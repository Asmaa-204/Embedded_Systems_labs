#include <avr/io.h>

#define F_CPU 16000000UL  // Define CPU frequency (16 MHz)

void Timer2_Init(void) {
    TCNT2 = 0;  // Initialize Timer2 counter to 0
    OCR2A = 250;  // Set Compare Match value for 15.625 kHz
    
    DDRB |= (1 << PB3);  // Set OC2A (PB3) as output pin
    
    // Configure Timer2 in CTC Mode
    TCCR2A = (1 << WGM21) | (1 << FOC2A) | (1 << COM2A0);  // CTC mode, Toggle OC2A on compare match
    TCCR2B = (1 << CS22) | (1 << CS20);  // Clock = F_CPU/128
}

void loop(){
    Timer2_Init();  // Initialize Timer2
}

int main(void) {
    
    while (1) {
        // Main loop does nothing, Timer2 handles output
    }
}
