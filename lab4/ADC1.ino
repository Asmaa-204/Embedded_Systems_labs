#include <avr/io.h> 

#define BAUD_RATE 9600


uint16_t readADC(uint8_t channel)
{
    channel &= 0x07; // Clearing all bit except the last three bits

    // F8 = 1111 1000
    // Leaving all bits and clearing the last three bits
    ADMUX = (ADMUX & 0xF8) | channel

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
    ADCSRA = (1 << ADEN);

    ADCSRA |= 0x07;
    // ADCSRA |= (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // Start Serial Communication
    Serial.begin(BAUD_RATE);
}


void loop()
{
    // Read X-axis (connected to A0/PC0)
    uint16_t xValue = readADC(0);
        
    // Read Y-axis (connected to A1/PC1)
    uint16_t yValue = readADC(1);

    // Print values to Serial Monitor
    Serial.print("X-axis = ");
    Serial.print(xValue);
    Serial.print("\t");  // Tab separator

    Serial.print("Y-axis = ");
    Serial.println(yValue);

    // Small delay to prevent overwhelming the Serial Monitor
    delay(100);
}