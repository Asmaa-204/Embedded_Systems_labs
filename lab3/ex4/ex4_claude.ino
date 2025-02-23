#include <avr/io.h>

void Timer2_Init(void) {
    // 1. Initialize Timer2 counter to 0
    TCNT2 = 0;
    
    // 2. Set Compare value
    OCR2A = 250;
    
    // 3. Set OC2A (PB3) as output pin
    DDRB |= (1 << PB3);
    
    // 4. Configure Timer2 Control Registers
    TCCR2A = (1 << COM2A0) |    // Toggle OC2A on compare match
             (1 << WGM21)  |    // CTC Mode
             (1 << FOC2A);      // Non-PWM mode
             
    TCCR2B = (1 << CS22) |     // Clock = F_CPU/128
             (1 << CS20);       // CS22=1, CS21=0, CS20=1
}

void setup(){
    Timer2_Init();
}

void loop(){
    
}