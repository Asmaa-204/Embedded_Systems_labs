
int counter;
void setup() {
  DDRC = DDRC & (~ (1 << PC4));
  DDRD = 0xFF;
  counter = 0;
 
}

void display(int counter)
{
  if(counter == 0){
    PORTD = 0x3F;
  }else if(counter == 1){
    PORTD = 0x06;
  }else if(counter == 2){
    PORTD = 0x5B;
  }else if(counter == 3){
    PORTD = 0x4F;
  }else if(counter == 4){
    PORTD = 0x66;
  }else if(counter == 5){
    PORTD = 0x6D;
  }else if(counter == 6){
    PORTD = 0x7D;
  }else if(counter == 7){
    PORTD = 0x07;
  }else if(counter == 8){
    PORTD = 0x7F;
  }else if(counter == 9){
    PORTD = 0x6F;
  }
}

void loop() {

  if((PINC & (1 << PC4)) != 0){
    _delay_ms(100);
    counter = counter + 1;
    counter = counter % 9;
    display(counter);
  }
  
}
