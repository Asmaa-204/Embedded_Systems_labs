#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#define BUTTON_PIN PD3

ISR(INT1_vect) {
  for (int i = 0; i < 5; i++) {
      PORTC |= (1 << PC0) | (1 << PC1) | (1 << PC2);
      _delay_ms(500);
      PORTC &= ~((1 << PC0) | (1 << PC1) | (1 << PC2));
      _delay_ms(500);
  }
}

void init_int1() {
  SREG &= (~(1 << 7));

  DDRD &= (~(1 << BUTTON_PIN));
  PORTD |= (1 << BUTTON_PIN);

  EICRA |= (1 << ISC10) | (1 << ISC11);
  EIMSK |= (1 << INT1);

  SREG |= (1 << 7);
}

void setup() {
  init_int1();
  DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2);
}

void loop() {
  for(int i = 0; i < 3; i++) {
    PORTC = 0x00;
    PORTC |= (1 << i);
    _delay_ms(500);
  }
}
