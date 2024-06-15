/** 
 * @file command.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-03-31
 * @brief This file handles command registration and execution
 */


#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "include/help.h"
#include "include/clear.h"
#include "include/led.h"
#include "include/IO.h"

#include "include/command.h"

// #define DEBUG // Use to print out the results of command extract etc
#define NUM_CMDS 4

#define MAX_SPACES 2 // the maximum number of spaces in a row in a command
#define ARG_SIZE 10 // the maximum length of an argument in chars

CMDs_t *cmd_init(void) {
    CMDs_t *p_commands = calloc(1, sizeof(CMDs_t));

    // initialise the commands
    CMD_t help = {
        .name = "help",
        .command = help_entry
    };

    CMD_t clear = {
        .name = "clear",
        .command = clear_entry
    };

    CMD_t led = {
        .name = "led",
        .command = led_entry
    };

    CMD_t IO = {
        .name = "IO",
        .command = IO_entry
    };

    p_commands->list = calloc(NUM_CMDS, sizeof(CMD_t));
    p_commands->list[0] = help;
    p_commands->list[1] = clear;
    p_commands->list[2] = led;
    p_commands->list[3] = IO;

    p_commands->length = NUM_CMDS;

    return p_commands;
}


uint8_t cmd_execute(CMDs_t commands, uint8_t argc, char **argv) {
    for (uint8_t i=0; i < commands.length; i++) {
#ifdef DEBUG
        printf("Checking %s\n", commands.list[i].name);
#endif // DEBUG
        if (strcmp(commands.list[i].name, argv[0]) == 0) {
#ifdef DEBUG
            printf("Executing: %s\n", commands.list[i].name);
#endif // DEBUG
            return commands.list[i].command(argc, argv);
        }
    }

    return 0;
}

uint16_t cmd_extract(char *s_input, uint8_t argc_max, char* argv[]) {
    bool first_space = true;
    bool new_arg = false;
    uint16_t arg_number = 0;
    uint16_t char_number = 0;


    argv[0] = (char *)calloc(ARG_SIZE, sizeof(char));

    for (uint16_t i = 0; i < strlen(s_input); i++) {

        if (s_input[i] == '\n') { // end of command
            return arg_number+1;

        } else if (s_input[i] == ' ') {
            if (first_space) { // ignore spaces between commands
                argv[arg_number][char_number] = '\0';

                new_arg = true;
                
                first_space = false;
            }
        } else {
            if (char_number < ARG_SIZE) {
                if (new_arg) {
                    arg_number++;
                    char_number = 0;

                    argv[arg_number] = (char *)calloc(ARG_SIZE, sizeof(char));

                    new_arg = false;
                }

                argv[arg_number][char_number] = s_input[i];

                char_number++;
                first_space = true; // must be at new arg

            } else {
                argv[arg_number][char_number] = '\0';
                return arg_number;
            }
        }
    }

    return arg_number;
}



bool cmd_check_input(char *cmd) {

    return 1;
}

void cmd_print_error(char *p_cmd) {
    printf("%s is not a valid cmd please try again \n \n", p_cmd);
}
