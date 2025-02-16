void setup() {
  DDRB = DDRB & (~ (1 << PB0));
  PORTB = PORTB | (1 << PB0);

  DDRC = DDRC | (1 << PC0);
  PORTC = PORTC & (~(1 << PC0));
  
}

void loop() {
  bool prev_state = 0;

  if((PINC & (1 << PB0)) != 0){
    _delay_ms(30);
  }

  if((PINC & (1 << PB0)) != 0){
    PORTC = PORTC ^ (1 << PC0);
  }
  
}
