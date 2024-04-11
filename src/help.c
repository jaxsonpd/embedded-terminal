/** 
 * @file help.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-04-06
 * @brief The help command module
 */


#include <stdint.h>
#include <stdbool.h>

#include "include/UART.h"

#include "help.h"




uint8_t HELP_entry(char* args) {
    UART_puts("Embedded Terminal version 0.1\n\n");

    UART_puts("Use info embeddedTerminal for more infomation about this shell\n");
    UART_puts("Commands marked with * are not implemented in this system\n");
    UART_puts("The following commands are available for the system:\n\n");
    
    UART_puts("help: print this message\n");
    UART_puts("clear: clear the screen\n");
    UART_puts("*info: display information about the command\n");
    UART_puts("*neofecth: displays information about this system\n");
    UART_puts("led: toggels the led connected to PB5\n");
    UART_puts("*digitalWrite: writes to a output of the microcontroller\n");

    return 0;
}
