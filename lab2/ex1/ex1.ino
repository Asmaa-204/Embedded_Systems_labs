#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PIN    PC0
#define BUTTON_PIN  PD2 

ISR(INT0_vect) {
  PORTC ^= (1 << PC0);
}

void init_int0() {
  SREG &= (~(1 << 7));

  DDRD &= (~(1 << BUTTON_PIN));
  EIMSK |= (1 << INT0);
  EICRA |= (1 << ISC00) | (1 << ISC01);

  SREG |= (1 << 7);
}

void setup() {
  init_int0();
  DDRC |= (1 << LED_PIN);
  PORTC &= ~(1 << LED_PIN);
}

void loop() {
}
