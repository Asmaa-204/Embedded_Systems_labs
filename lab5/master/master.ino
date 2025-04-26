#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <Arduino.h>

void spi_init_master() {
    // Set MOSI, SCK, SS as Output
    DDRB = (1 << DD2) | (1 << DD3) | (1 << DD5);

    // Set MISO as input
    DDRB &= ~(1 << DD4);

    PORTB |= (1 << DD2);
  
    // Enable SPI, Set as Master, Prescaler: Fosc/16
    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
}

void spi_write(uint8_t data) {
    // Start transmission
    SPDR = data;

    // Wait for transmission to complete
    while (!(SPSR & (1 << SPIF)));

    volatile char flush_buffer = SPDR; // Read SPDR to clear SPIF flag
    flush_buffer += 1;
}

uint8_t spi_read() {
    // Start transmission with dummy data
    SPDR = 0xFF;

    // Wait for reception to complete
    while (!(SPSR & (1 << SPIF)));

    // Return received data
    return SPDR;
}

int main(void) {
    Serial.begin(9600);
    spi_init_master();

    // Set SS low to select the slave
    PORTB &= ~(1 << PB2);

    // Wait for the slave to be ready
    _delay_ms(300);

    uint8_t i = 1;
    while (1) {
        // Reset i to 1 after reaching 100
        if (i > 100) {
          i = 1; 
        }
        spi_write(i); // Send data to the slave
        _delay_ms(10);
        uint8_t received_data = spi_read(); // Read data from the slave
        Serial.print(received_data); // Print received data to the serial monitor'
        Serial.print(" ");
        Serial.println(i++);
        _delay_ms(300);
    }
}