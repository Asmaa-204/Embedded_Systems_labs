#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <Arduino.h>

#define SS PB2 // Slave Select pin
#define MOSI PB3 // Master Out Slave In pin
#define MISO PB4 // Master In Slave Out pin
#define SCK PB5 // Serial Clock pin

void spi_init_slave() {
    // Set MISO as Output
    DDRB = (1 << MISO);

    // Set MOSI, SCK, SS as input
    DDRB &= ~((1 << MOSI) | (1 << SCK) | (1 << SS));
  
    // Enable SPI in slave mode
    SPCR = (1 << SPE);
}

void spi_write(uint8_t data) {
    // Start transmission
    SPDR = data;

    // Wait for transmission to complete
    while (!(SPSR & (1 << SPIF)));

    volatile char flush_buffer = SPDR; // Read SPDR to clear SPIF flag
}

uint8_t spi_read() {
    SPDR = 0xFF;

    // Wait for reception to complete
    while (!(SPSR & (1 << SPIF)));

    // Return received data
    return SPDR;
}

int main(void) {
    Serial.begin(9600);
    spi_init_slave();

    uint8_t received_data = 0;

    while (1) {
        //read from master
        received_data = spi_read();
        Serial.println(received_data);

        //write to master
        received_data += 100; // Increment the received data
        spi_write(received_data); // Send data back to the master
    }
}