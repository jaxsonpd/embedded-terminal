/** 
 * @file UART_Test.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-03-30
 * @brief A file to test the uart interface on the avr microcontrollers
 * 
 * 
 * @cite http://www.rjhcoding.com/avrc-uart.php
 */


#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

#include "UART.h"

#define F_CPU 16000000UL


void UART_init (uint16_t baud) {
    // initalise the baudrate
    unsigned long ubrr = (((F_CPU) + 8UL * (baud)) / (16UL * (baud))) - 1UL;

    UBRR0L = (uint8_t)(ubrr & 0xFF);
    UBRR0H = (uint8_t)(ubrr >> 8);

    // enable the uart pins
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);    
}


void UART_putc (unsigned char data) {
    // wait for transmit buffer to be empty
    while(!(UCSR0A & (1 << UDRE0)));

    // load data into transmit register
    UDR0 = data;
}


void UART_puts(char* s) {
    // Transmit until null is reached
    while (*s > 0) {
        UART_putc (*s++);
    }
}

void UART_puthex8(uint8_t val) {
    // extract hex values
    uint8_t upperNibble = (val & 0xF0) >> 4;
    uint8_t lowerNibble = val & 0x0F;

    // convert to ascii
    upperNibble += upperNibble > 9 ? 'A' - 10 : '0';
    lowerNibble += lowerNibble > 9 ? 'A' - 10 : '0';

    UART_putc(upperNibble);
    UART_putc(lowerNibble);
}



unsigned char UART_getc(void) {
    // Wait until buffer is full
    while(!(UCSR0A & (1 << RXC0)));

    // return the data
    return UDR0;
}


uint16_t UART_getLine(char* p_buffer, uint16_t bufferLength) {
    uint16_t bufIdx = 0;
    char c;

    // add to the buffer until run out of room or EOL is recived
    do {
        c = UART_getc();

        p_buffer[bufIdx++] = c;
    } while ((bufIdx < bufferLength) && (c != '\r') && (c != '\n'));

    // Ensure that line terminations are correct
    if (c == '\r') {
        p_buffer[bufIdx-1] = '\n';
    }

    p_buffer[bufIdx] = '\0';

    return bufIdx; 
}

uint16_t UART_getLineWithEcho(char* p_buffer, uint16_t bufferLength) {
    uint16_t bufIdx = 0;
    char c;

    // add to the buffer until run out of room or EOL is recived
    do {
        c = UART_getc();

        if (c == '\r') {
            UART_putc('\n');
        } else {
            UART_putc(c);
        }

        p_buffer[bufIdx++] = c;
    } while ((bufIdx < bufferLength) && (c != '\r') && (c != '\n'));

    // Ensure that line terminations are correct
    if (c == '\r') {
        p_buffer[bufIdx-1] = '\n';
    }

    p_buffer[bufIdx] = '\0';

    return bufIdx; 
}