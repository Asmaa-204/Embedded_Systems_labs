#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL  // Define CPU frequency (16 MHz)
#define PRESCALER 256     // Timer prescaler
#define TIMER0_OVF_COUNT 62 // Number of overflows needed for ~1 sec delay

// 7-segment display common cathode numbers
const uint8_t seven_seg_digits[10] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

volatile uint8_t overflow_count = 0;
volatile uint8_t digit = 0;

void Timer0_Init(void) {
    TCNT0 = 0;  // Initialize Timer0 counter to 0
    
    // Configure Timer0 in Normal Mode
    TCCR0B = (1 << CS02);  // Clock = F_CPU/256
    TIMSK0 = (1 << TOIE0);  // Enable Timer0 overflow interrupt
    
    sei();  // Enable global interrupts
}

// ISR(TIMER0_OVF_vect) {
//     overflow_count++;
//     if (overflow_count >= TIMER0_OVF_COUNT) {
//         digit = (digit + 1) % 10;  // Increment digit and reset at 9
//         PORTC = seven_seg_digits[digit];  // Display digit on 7-segment
//         overflow_count = 0;  // Reset overflow counter
//     }
// }

ISR(TIMER0_OVF_COUNT){
    overflow_count++;
    if(overflow >= 244) {
        if(TCNT0 >= 36) {
          TCNT0 = 0;
          overflow = 0;
          digit = (digit + 1) % 10;
          PORTC = segment_codes[digit];
        }
    }
}

void setup(){
    DDRC = 0xFF;  // Set PORTC as output for 7-segment
    PORTC = seven_seg_digits[0];  // Start at 0
    
    Timer0_Init();  // Initialize Timer0
}

void loop(){

}
