//not working

#include <avr/io.h>
#include <Arduino.h>
#include <util/delay.h>

unsigned int t;

void setup(){
    DDRA = 0xFF;
    DDRB = 0XFF;
    PORTD = 0XFF;

    TCCR1A = 0;
    TIFR   = (1 << ICF1);
    TCCR1B = 0X41;
    Serial.begin(9600);
}


void loop(){
    while((TIFR & (1 << ICF1)) == 0);

    t = ICR1 - t;

    Serial.print("Period: ");
    Serial.println(t);  

    _delay_ms(100);
}