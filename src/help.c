/** 
 * @file help.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-04-06
 * @brief The help command module
 */


#include <stdint.h>
#include <stdbool.h>




uint8_t HELP_entry(char* args) {
    UART_puts("Embedded Terminal version 0.1\n");
    UART_puts("The following commands are available for the system:\n\n");
    UART_puts("help: print this message\n");

    return 0;
}
