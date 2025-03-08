#include <avr/io.h>    
#include <avr/interrupt.h> 

#define BAUD_RATE 9600

volatile uint16_t xValue = 0;    // X-axis ADC value
volatile uint16_t yValue = 0;    // Y-axis ADC value
volatile uint8_t channel = 0;    // Current ADC channel (0 or 1), 8-bit is sufficient

void adcread(uint8_t ch) {
    ADMUX = (ADMUX & 0xF0) | (ch & 0x07);  // Select channel (0-7)
    ADCSRA |= (1 << ADSC);                  // Start conversion
}

ISR(ADC_vect) {
    uint16_t adcValue = ADC;
    
    if (channel == 0) {
        xValue = adcValue;
        channel = 1;       // Switch to Y-axis (A1)
    } else {
        yValue = adcValue;
        channel = 0;       // Switch back to X-axis (A0)
    }

    adcread(channel);      // Start next conversion
}

void setup() {
    // Set AREF = VCC (AVCC)
    // 0100 0000 = 0x40
    ADMUX = (1 << REFS0);

    ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

    // Initialize Serial
    Serial.begin(BAUD_RATE);

    // Enable global interrupts
    sei();

    // Start first conversion on channel 0 (X-axis)
    adcread(0);
}

void loop() {
    // Safely read volatile variables
    noInterrupts();
    uint16_t x = xValue;
    uint16_t y = yValue;
    interrupts();
    
    // Print values
    Serial.print("X-axis = ");
    Serial.print(x);
    Serial.print("\t");
    Serial.print("Y-axis = ");
    Serial.println(y);
    
    delay(100);  // Control display rate
}