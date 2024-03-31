/** 
 * @file main.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-03-30
 * @brief The main file for the embedded Terminal project
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <util/delay.h>

#include "include/UART.h"


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
 * @brief exctract the command from an input buffer
 * @param p_input a pointer to the input string
 * @param inputSize the size of the input string
 * @param p_cmd a pointer to the command string
 * @param maxCMDLength the size of the command string
 * @param p_args a pointer to the args string
 * @param maxArgsLength the size of the args string
 * 
 */
void extract_cmd(char* p_input, uint16_t inputSize, char* p_cmd, uint16_t maxCMDLength, char* p_args, uint16_t maxArgsLength) {
    strcpy(p_cmd, p_input);
}


/** 
 * @brief check if the inputed command is an excutable
 * @param cmd the command to check
 * 
 * @return 1 if excutable 0 otherwise
 */
bool check_input(char* cmd) {

    return 1;
}


/** 
 * @brief excute the command with the give arguments
 * @param p_cmd a pointer to the command string
 * @param p_args a pointer to the arguments string
 */
void excute(char* p_cmd, char* p_args) {
    UART_puts("Excuted: ");
    UART_puts(p_cmd);
    UART_puts("\n");
}


/** 
 * @brief print an error as the given command is not an excutable
 * @param p_cmd the command that is not excutable
 * 
 */
void print_error(char* p_cmd) {
    UART_puts(p_cmd);
    UART_puts(" is not a valid cmd please try again \n \n");
}


/** 
 * @brief Setup for the embedded terminal
 * 
 * @return 1 if successful 0 otherwise
 */
bool setup (void) {
    // initalise comunications
    UART_init(BAUD_RATE);

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

        const uint16_t c_maxInputSize = 20;
        char p_input[c_maxInputSize];

        uint16_t inputSize = UART_getLine(p_input, c_maxInputSize);

        UART_puts(p_input);
        // UART_putc('\n');

        const uint16_t c_maxCMDLength = 10;
        const uint16_t c_maxArgsLength = 10;

        char p_cmd[c_maxCMDLength];
        char p_args[c_maxArgsLength];

        extract_cmd(p_input, inputSize, p_cmd, c_maxCMDLength, p_args, c_maxArgsLength);

        if (inputSize == 1) {
            // Not a command so do not throw an error
        } if (check_input(p_cmd)) {
            // input is a valid command
            excute(p_cmd, p_args);
        } else {
            // input is an error
            print_error(p_cmd);
        }
    }

}
