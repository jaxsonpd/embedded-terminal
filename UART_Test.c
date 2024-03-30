/** 
 * @file UART_Test.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-03-30
 * @brief A file to test the uart interface on the avr microcontrollers
 * 
 * @cite http://www.rjhcoding.com/avrc-uart.php
 */


#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>


#define F_CPU 16000000UL



#define MS_DELAY 200


/** 
 * @brief Initalise the UART interface to the give baud rate
 * 
 * uBRRn = f_osc/(16 * baud)-1
 * 
 * @param ubrr the baud rate of the serial transmistions already divided by the clock
 * 
 */
void UART_init (uint16_t baud) {
    // initalise the baudrate
    unsigned long ubrr = (((F_CPU) + 8UL * (baud)) / (16UL * (baud))) - 1UL;

    UBRR0L = (uint8_t)(ubrr & 0xFF);
    UBRR0H = (uint8_t)(ubrr >> 8);

    // enable the uart pins
    UCSR0B |= (1 << RXEN0) | (1 << TXEN0);    
}


/** 
 * @brief put a char to the serial buffer
 * @param data a char to put to the serial buffer
 * 
 */
void UART_putc (unsigned char data) {
    // wait for transmit buffer to be empty
    while(!(UCSR0A & (1 << UDRE0)));

    // load data into transmit register
    UDR0 = data;
}


/** 
 * @brief Print a string to uart
 * @param s the string to print
 * 
 */
void UART_puts(char* s) {
    // Transmit until null is reached
    while (*s > 0) {
        UART_putc (*s++);
    }
}


/** 
 * @brief Recive a char from the uart buffer
 * 
 * @return the char recived
 */
unsigned char UART_getc(void) {
    // Wait until buffer is full
    while(!(UCSR0A & (1 << RXC0)));

    // return the data
    return UDR0;
}


/** 
 * @brief Get a whole line from the uart buffer 
 * @param p_buffer a pointer to a char array where the string will be stored
 * @param bufferLength the length of the buffer
 * 
 * @return the resulting length of the line
 */
uint16_t UART_getLine(char* p_buffer, uint16_t bufferLength) {
    uint16_t bufIdx = 0;
    char c;

    // add to the buffer until run out of room or EOL is recived
    do {
        c = UART_getc();

        p_buffer[bufIdx++] = c;
    } while ((bufIdx < bufferLength) && (c != '\r') && (c != '\n'));

    p_buffer[bufIdx] = '\0';

    return bufIdx; 
}



int main (void) {
    UART_init(9600);
    UART_puts("Hello World \n");

    while (1) {
        uint16_t bufferSize = 20;
        char p_buffer[bufferSize];

        uint16_t result = UART_getLine(p_buffer, bufferSize);

        UART_puts(p_buffer);
    }
}




