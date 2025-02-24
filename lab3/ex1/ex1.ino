#include <avr/io.h>
#include <avr/interrupt.h>

volatile uint8_t overflow = 0;

void timer2_init() { 
  TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20);
  TCNT2 = 0; 
  TIMSK2 |= (1 << TOIE2);
  sei();
}

ISR(TIMER2_OVF_vect) {
  overflow++;
}

int main () {
  DDRC |= (1 << PC0);
  PORTC &= ~(1 << PC0);
  timer2_init();

  while(true) {
    if(overflow >= 30) {
      if(TCNT2 >= 132) {
        PORTC ^= (1 << PC0);
        TCNT2 = 0;
        overflow = 0;
      }
    }
  }
}
