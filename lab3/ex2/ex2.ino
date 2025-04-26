#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t overflow = 0;
volatile uint8_t digit = 0;

// for common cathode
uint8_t segment_codes[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F};

void timer2_init() { 
  // 256 prescalar for timer 2
  TCCR2B |= (1 << CS22) | (1 << CS21);
  TCNT2 = 0; 
  TIMSK2 |= (1 << TOIE2);
  sei();
}

ISR(TIMER2_OVF_vect) {
  overflow++;
}

int main () {
  DDRD = 0xFF;
  PORTD = segment_codes[0];
  timer2_init();

  while(true) {
    if(overflow >= 244) {
      if(TCNT2 >= 35) {
        PORTD = segment_codes[digit];
        TCNT2 = 0;
        overflow = 0;
        digit = (digit + 1) % 10;
      }
    }
  }
}
