#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL    // Define CPU frequency (16 MHz)
#define PRESCALER 1024      // Timer prescaler

// Calculate OCR2A value for 0.5s interval
// F_CPU / (2 * PRESCALER * desired_frequency) - 1
// 16000000 / (2 * 1024 * 1) - 1 = 124
#define OCR2A_VALUE 124

volatile uint8_t toggle_count = 0;


// Initialize Timer2 counter to 0
// Configure Timer2 in CTC Mode
// Clock = F_CPU/1024
// Set compare match value
// Enable Timer2 compare match interrupt
// Enable global interrupts

void Timer2_Init(void) {
    TCNT2 = 0;    
     
    TCCR2B |= (1 << CS22) | (1 << CS21) | (1 << CS20) | ( 1<< WGM12 );   
    
    OCR2A = OCR2A_VALUE;    
    
    TIMSK2 |= (1 << OCIE2A);    
    
    sei();    
}

ISR(TIMER2_COMPA_vect) {
    toggle_count++;
    if (toggle_count >= 2) {    // Toggle every 2 compare matches (for 0.5s)
        PORTC ^= (1 << PC0);    // Toggle LED
        toggle_count = 0;       // Reset count
    }
}

void setup(){
    DDRC |= (1 << PC0);       
    PORTC &= ~(1 << PC0);
    Timer2_Init();           
}

void loop(){
    
}