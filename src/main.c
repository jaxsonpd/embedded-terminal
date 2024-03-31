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
    return 1;
} 


int main (void) {
    // Setup
    if (!setup()) {
        while (1) {
            UART_puts("Setup Fault");

            _delay_ms(1000);            
        }
    }

    while (1) {
        print_prompt();

        uint16_t c_maxInputSize = 64;
        char p_input[c_maxInputSize];


        uint16_t inputSize = UART_getLineWithEcho(p_input, c_maxInputSize);

        uint16_t c_maxCMDLength = 64;
        uint16_t c_maxArgsLength = 64;

        char* p_cmd = (char *)calloc(c_maxCMDLength, sizeof(char));
        char* p_args = (char *)calloc(c_maxArgsLength, sizeof(char));

        CMD_extract(p_input, inputSize, p_cmd, c_maxCMDLength, p_args, c_maxArgsLength);

        if (inputSize == 1) {
            // Not a command so do not throw an error
        } else if (CMD_checkInput(p_cmd)) {
            // input is a valid command
            CMD_execute(p_cmd, p_args);
        } else {
            // input is an error
            CMD_printError(p_cmd);
        }

        free(p_cmd);
        free(p_args);
    }

}
