/** 
 * @file main.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-03-30
 * @brief The main file for the embedded Terminal project
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include <util/delay.h>

#include "include/UART.h"
#include "include/command.h"


#define BAUD_RATE 9600


uint8_t HELP_entry(char* args) {
    UART_puts("Embedded Terminal version 0.1\n");
    UART_puts("The following commands are available for the system:\n\n");
    UART_puts("help: print this message\n");

    return 0;
}


CMD_t help;

CMDs_t g_commands; 


/** 
 * @brief Print a prompt to the screen
 * 
 */
void print_prompt (void) {
    char p_prompt[3] = "$>";
    UART_puts(p_prompt);
}


/** 
 * @brief Print the welcome screen
 * 
 */
void print_welcome (void) {
    UART_puts("**************************\n");

    UART_puts("Embedded Terminal v0.1\n");    
    UART_puts("Created by: Jack Duignan\n");
    UART_puts("Max input size: 64 chars, Use help for more info\n");

    UART_puts("**************************\n");

}


/** 
 * @brief Setup for the embedded terminal
 * 
 * @return 1 if successful 0 otherwise
 */
bool setup (void) {
    // initalise comunications
    UART_init(BAUD_RATE);

    print_welcome();

    help.name = calloc(5, sizeof(char));
    strcpy(help.name, "help");

    UART_puts(help.name);

    help.command = HELP_entry;

    g_commands.list = calloc(1, sizeof(CMD_t));
    g_commands.list[0] = help;
    g_commands.length = 1;

    return true;
} 


int main (void) {
    // Setup
    setup();

    while (1) {
        print_prompt();

        uint16_t c_maxInputSize = 64;
        char input[c_maxInputSize];


        uint16_t inputSize = UART_getLineWithEcho(input, c_maxInputSize);

        uint16_t c_maxCMDLength = 64;
        uint16_t c_maxArgsLength = 64;

        char* cmd = (char *)calloc(c_maxCMDLength, sizeof(char));
        char* args = (char *)calloc(c_maxArgsLength, sizeof(char));

        CMD_extract(input, inputSize, cmd, c_maxCMDLength, args, c_maxArgsLength);

        if (inputSize == 1) {
            // Not a command so do not throw an error
        } else if (CMD_checkInput(cmd)) {
            // input is a valid command
            CMD_execute(g_commands, cmd, args);
        } else {
            // input is an error
            CMD_printError(cmd);
        }

        free(cmd);
        free(args);
    }

}
