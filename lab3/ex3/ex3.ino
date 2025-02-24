#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t overflow = 0;

ISR(TIMER2_COMPA_vect) {
  overflow++;
}

void timer2_init() { 
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
  TCCR1B |= (1 << WGM12);
  TIMSK2 = (1 << OCIE2A);
  OCR2A = 255;
  TCNT2 = 0; 
  sei();
}

void setup() {
  DDRC |= (1 << PC0);
  PORTC &= ~(1 << PC0);
  timer2_init();
}

void loop() {
  if(overflow >= 30) {
    if(TCNT2 >= 132) {
      PORTC ^= (1 << PC0);
      overflow = 0;
      TCNT2 = 0;
    }
  }
}
