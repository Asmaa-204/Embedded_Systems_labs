#include <avr/io.h>
#include <Arduino.h>

void Timer1_Init(void) {
    // Configure ICP1 (PB0) as input
    DDRB &= ~(1 << PB0);
    
    // Initialize Timer1
    TCCR1A = 0;  // Normal mode
    
    // Configure for rising edge capture, no prescaler
    TCCR1B = (1 << ICES1) |  // Rising edge capture
             (1 << CS10);     // No prescaler, clock = F_CPU
             
    // Clear Timer counter
    TCNT1 = 0;
    
    // Clear input capture flag
    TIFR1 = (1 << ICF1);
}

void setup() {
    Serial.begin(9600);  // Initialize serial communication
    Timer1_Init();       // Initialize Timer1
}

void loop() {
    uint16_t captureTime1, captureTime2, period;
    
    // Wait for first rising edge capture
    while ((TIFR1 & (1 << ICF1)) == 0);  // Wait until ICF1 is set
    
    // Store first capture time
    captureTime1 = ICR1;
    
    // Clear capture flag by writing 1 to it
    TIFR1 = (1 << ICF1);
    
    // Wait for next rising edge capture
    while ((TIFR1 & (1 << ICF1)) == 0);  // Wait until ICF1 is set
    
    // Store second capture time
    captureTime2 = ICR1;
    
    // Clear capture flag
    TIFR1 = (1 << ICF1);
    
    // Calculate period (in timer counts)
    period = captureTime2 - captureTime1;
    
    // Print period to serial monitor
    Serial.print("Period (timer counts): ");
    Serial.println(period);
    
    // Calculate frequency (Hz)
    float frequency = (F_CPU / (float)period);
    Serial.print("Frequency (Hz): ");
    Serial.println(frequency);
    Serial.println();
    
    delay(100);  // Small delay before next measurement
}