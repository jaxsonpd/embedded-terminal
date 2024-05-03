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




uint8_t help_entry(uint16_t argc, char **argv) {
    printf("Embedded Terminal version 0.1\n\n");

    printf("Use info embeddedTerminal for more infomation about this shell\n");
    printf("Commands marked with * are not implemented in this system\n");
    printf("The following commands are available for the system:\n\n");
    
    printf("help: print this message\n");
    printf("clear: clear the screen\n");
    printf("*info: display information about the command\n");
    printf("*neofecth: displays information about this system\n");
    printf("led: toggels the led connected to PB5\n");
    printf("*digitalWrite: writes to a output of the microcontroller\n");

    return 0;
}
