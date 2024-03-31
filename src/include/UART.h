/** 
 * @file UART.h
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-03-30
 * @brief A uart module for simple serial comunication
 */


#ifndef UART_H
#define UART_H

/** 
 * @brief Initalise the UART interface to the give baud rate
 * 
 * uBRRn = f_osc/(16 * baud)-1
 * 
 * @param ubrr the baud rate of the serial transmistions already divided by the clock
 * 
 */
void UART_init (uint16_t baud);


/** 
 * @brief put a char to the serial buffer
 * @param data a char to put to the serial buffer
 * 
 */
void UART_putc (unsigned char data);


/** 
 * @brief Print a string to uart
 * @param s the string to print
 * 
 */
void UART_puts(char* s);


/** 
 * @brief Recive a char from the uart buffer
 * 
 * @return the char recived
 */
unsigned char UART_getc(void);


/** 
 * @brief Get a whole line from the uart buffer 
 * @param p_buffer a pointer to a char array where the string will be stored
 * @param bufferLength the length of the buffer
 * 
 * @return the resulting length of the line
 */
uint16_t UART_getLine(char* p_buffer, uint16_t bufferLength);

#endif // UART_H