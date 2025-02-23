#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL  // Define CPU frequency (16 MHz)
#define PRESCALER 1024    // Timer prescaler
#define TIMER2_OVF_COUNT 31 // Number of overflows needed for ~0.5 sec delay

volatile uint8_t ovf_count = 0;

void Timer2_Init(void) {
    TCNT2 = 0;  // Initialize Timer2 counter to 0
    
    
    TCCR2A = (1 << FOC2A);  // Non-PWM mode
    TCCR2B = (1 << CS22) | (1 << CS21) | (1 << CS20);  // Clock = F_CPU/1024
    
    TIMSK2 = (1 << TOIE2);  // Enable Timer2 overflow interrupt
    
    sei();  // Enable global interrupts
}

ISR(TIMER2_OVF_vect) {
    ovf_count++;
    if (ovf_count >= TIMER2_OVF_COUNT) {
        PORTC ^= (1 << PC0);  // Toggle LED
        ovf_count = 0;  // Reset overflow count
    }
}

void setup()
{
    DDRC |= (1 << PC0);  // Set PC0 as output
    PORTC &= ~(1 << PC0);  // Ensure LED is off initially (Positive Logic)
    
    Timer2_Init();  // Initialize Timer2
}

void loop()
{

}


