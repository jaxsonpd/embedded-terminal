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
#include <stdio.h>

#include <avr/io.h>
#include <util/delay.h>

#include "include/UART.h"
#include "include/GPIO.h"

#include "utils.h"
#include "command.h"


#define BAUD_RATE 9600

CMDs_t *p_commands;

uint16_t g_testpin = PIN(((const uint8_t)&PORTB), PORTB5);

/** 
 * @brief Print a prompt to the screen
 * 
 */
void print_prompt (void) {
    char p_prompt[3] = "$>";
    printf(p_prompt);
}


/** 
 * @brief Print the welcome screen
 * 
 */
void print_welcome (void) {
    printf("**************************\r\n");

    printf("Embedded Terminal v0.1\r\n");    
    printf("Created by: Jack Duignan\r\n");
    printf("Max input size: 64 chars, Use help for more info\r\n");

    printf("**************************\r\n");

}


/** 
 * @brief Setup for the embedded terminal
 * 
 * @return 1 if successful 0 otherwise
 */
bool setup (void) {
    // initalise comunications
    UART_init_stdio(BAUD_RATE);

    GPIO_pinInit(g_testpin, OUTPUT);

    GPIO_setOutput(g_testpin, 1);

    print_welcome();

    p_commands = CMD_setup();

    return true;
} 


int main (void) {
    // Setup
    setup();

    while (1) {
        // print_prompt();

        uint16_t c_maxInputSize = 64;
        char input[c_maxInputSize];

        UTL_getLine ("AVR:~$", input, c_maxInputSize);
        printf("%s\r\n", input);

        uint16_t c_maxCMDLength = 64;
        uint16_t c_maxArgsLength = 64;

        char* cmd = (char *)calloc(c_maxCMDLength, sizeof(char));
        char* args = (char *)calloc(c_maxArgsLength, sizeof(char));

        CMD_extract(input, 40, cmd, c_maxCMDLength, args, c_maxArgsLength);

        if (1 == 1) {
            // Not a command so do not throw an error
        } else if (CMD_checkInput(cmd)) {
            // input is a valid command
            CMD_execute(*p_commands, cmd, args);
        } else {
            // input is an error
            CMD_printError(cmd);
        }

        free(cmd);
        free(args);
    }

}
