#include <avr/io.h> 

#define BAUD_RATE 9600

uint16_t readADC(uint8_t channel)
{
    channel &= 0x07; // Clearing all bit except the last three bits

    // Leaving all bits and clearing the last three bits
    ADMUX = (ADMUX & 0xF8) | channel;

    // Start converting
    ADCSRA |= (1 << ADSC);

    // Wait until the conversion is done
    while(ADCSRA & (1 << ADSC));

    return ADC;
}


void setup() {
    // Setting REFS0 = 1 for Setting VRef = Vcc
    ADMUX = (1 << REFS0);

    // Enable ADC Mode and prescaler to 128
    ADCSRA = (1 << ADEN) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // Start Serial Communication
    Serial.begin(BAUD_RATE);
}


void loop()
{
    // Read X-axis (connected to A0/PC0)
    int value = readADC(0);
    Serial.println(value);
    delay(100);
}