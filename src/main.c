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
    printf("**************************\n");

    printf("Embedded Terminal v0.1\n");    
    printf("Created by: Jack Duignan\n");
    printf("Max input size: 64 chars, Use help for more info\n");

    printf("**************************\n");

}


/** 
 * @brief Setup for the embedded terminal
 * 
 * @return 1 if successful 0 otherwise
 */
bool setup (void) {
    // initialise communications
    UART_init_stdio(BAUD_RATE);

    print_welcome();

    p_commands = cmd_init();

    return true;
} 


int main (void) {
    // Setup
    setup();

    while (1) {
        // print_prompt();

        uint16_t c_maxInputSize = 64;
        char *input = (char *)calloc(c_maxInputSize, sizeof(char));

        utils_get_line_echo ("AVR:~$", input, c_maxInputSize);
        
        printf("Input: %s\n", input);

        uint16_t c_argc_max = 64;

        char** argv = (char **)calloc(c_argc_max, sizeof(char *));

        uint8_t argc = cmd_extract(input, c_argc_max, argv);

        printf("Args (%d): \n", argc);

        for (int i = 0; i < argc; i++) {
            printf("%d: %s\n", i, argv[i]);
        }

        if (argc) {
            cmd_execute(*p_commands, argc, argv);
        }

        for (int i = 0; i < argc; i++) {
            free(argv[i]);
        }

        free (argv);
    }

}
