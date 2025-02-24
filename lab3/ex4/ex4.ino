#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint16_t tot_overflow = 0;
volatile double period = 0;
volatile double firstTime = 0;
volatile double secondTime = 0;
volatile uint8_t first = 1;

ISR(TIMER1_OVF_vect) {
  if (!first) {
    tot_overflow++;
  }
}

ISR(TIMER1_CAPT_vect) {
  double clock_period = 6.25e-8;

  if (first) {
    firstTime = ICR1 * clock_period;
    first = 0;
    Serial.print("First Time: ");
    Serial.println(firstTime, 8);
  } 
  else {
    secondTime = ICR1 * clock_period;
    
    double totalTime = secondTime + ((tot_overflow * 65536.0) * clock_period);
    Serial.print("Second Time: ");
    Serial.println(totalTime, 8);

    period = totalTime - firstTime;

    first = 1;
    tot_overflow = 0;
    TCNT1 = 0;
  }

  TIFR1 = (1 << ICF1); // Clear flag
}

void timer1_init() {
  TCCR1A = 0;
  TCCR1B = (1 << CS10) | (1 << ICES1);
  TCCR1B |= (1 << ICNC1);
  TIMSK1 = (1 << ICIE1) | (1 << TOIE1);
  TCNT1 = 0;
  sei();
}

void setup() {
  DDRB &= ~(1 << PB0);
  timer1_init();
  Serial.begin(9600);
}

void loop() {
  if (period > 0) {
    Serial.print("Period: ");
    Serial.println(period, 8);
    period = 0;
    tot_overflow = 0;
  }
}