void setup() {
  DDRB = DDRB & (~ (1 << PB0));
  DDRB = DDRB & (~ (1 << PB1));

  DDRC = DDRC | (1 << PC0);
  DDRC = DDRC | (1 << PC1);
  
  PORTC = PORTC & (~ (1 << PC0));
  PORTC = PORTC & (~ (1 << PC1));

  Serial.begin(9600);
}

void loop() {
  if((PINB & (1 << PB0)) != 0){
     PORTC = PORTC | (1 << PC0);
     Serial.println("switch 1 is on");
  }else{
    PORTC = PORTC & (~ (1 << PC0));
  }

  if((PINB & (1 << PB1)) != 0){
   PORTC = PORTC | (1 << PC1);
   Serial.println("switch 2 is on");
  }else{
   PORTC = PORTC & (~ (1 << PC1));
  }

  _delay_ms(1000);
}
