#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t overflow = 0;
volatile uint8_t digit = 0;
uint8_t segment_codes[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

ISR(TIMER0_OVF_vect) {
  overflow++;
}

void timer0_init() { 
  TCCR2B = (1 << CS02);
  TCNT0 = 0; 
  TIMSK0 = (1 << TOIE0);
  sei();
}

void setup() {
  DDRD = 0xFF;
  PORTD = segment_codes[digit];
  timer0_init();
}

void loop() {
  if(overflow >= 244) {
    if(TCNT0 >= 36) {
      TCNT0 = 0;
      overflow = 0;
      digit = (digit + 1) % 10;
      PORTD = segment_codes[digit];
    }
  }
}
