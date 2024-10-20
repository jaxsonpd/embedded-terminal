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

#include "avr_extends/UART.h"
#include "avr_extends/GPIO.h"
#include "avr_extends/wire.h"

#include "inc/utils.h"
#include "inc/command.h"


#define BAUD_RATE 115200
// #define DEBUG

CMDs_t* p_commands;


/**
 * @brief Print the welcome screen
 *
 */
void print_welcome(void) {
    printf("**************************\r\n");

    printf("Embedded Terminal v0.1\r\n");
    printf("Created by: Jack Duignan\r\n");
    printf("Max input size: 64 chars, Use help for more info\r\n");

    printf("**************************\r\n");

}


/**
 * @brief Setup for the embedded terminal
 *
 * @return 0 if successful 1 otherwise
 */
bool setup(void) {
    // initialise communications
    UART_init_stdio(BAUD_RATE);

    print_welcome();

    p_commands = cmd_init();

    return false;
}


/**
 * @brief Free the memory used to store the argument array
 * @param argv the argument array
 * @param argc the number of arguments in the array
 */
void free_argv(char* argv[], int8_t argc) {
    free(argv[0]);

    for (uint8_t i = 1; i < argc; i++) {
        free(argv[i]);
    }

    free(argv);
}


int main(void) {
    // Setup
    setup();

    wire_init(100000);

    while(true) {
        wire_write(0x07, 0x43);
        _delay_ms(100);
    }
    while (1) {
        uint16_t c_maxInputSize = 64;
        char* input = (char*)calloc(c_maxInputSize, sizeof(char));
        utils_get_line_echo("AVR:~$", input, c_maxInputSize);


        uint8_t c_argc_max = 64;
        char** argv = (char**)calloc(c_argc_max, sizeof(char*));
        uint8_t argc = cmd_extract(input, c_argc_max, argv);

#ifdef DEBUG
        printf("Input: %s\r\n", input);
        printf("Args (%d): \r\n", argc);

        for (uint8_t i = 0; i < argc; i++) {
            printf("%d: %s\r\n", i, argv[i]);
        }
#endif // DEBUG

        if (argc) {
            cmd_execute(*p_commands, argc, argv);
        }

        free(input);

        free_argv(argv, argc);
    }
}
