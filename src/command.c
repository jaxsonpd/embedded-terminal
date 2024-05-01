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

#include "help.h"
#include "clear.h"
#include "led.h"

#include "command.h"

// #define DEBUG // Use to print out the results of command extract etc
#define NUM_CMDS 3
#define MAX_SPACES 2 // the maximum number of spaces in a row in a command


CMDs_t *cmd_init(void) {
    CMDs_t *p_commands = calloc(1, sizeof(CMDs_t));

    // inilise the commands
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

    p_commands->list = calloc(NUM_CMDS, sizeof(CMD_t));
    p_commands->list[0] = help;
    p_commands->list[1] = clear;
    p_commands->list[2] = led;

    p_commands->length = NUM_CMDS;

    return p_commands;
}


void cmd_execute(CMDs_t commands, char *cmd, char *args) {
    for (uint8_t i=0; i < commands.length; i++) {
        if (strcmp(commands.list[i].name, cmd) == 0) {
            commands.list[i].command(args);
        }
    }
}

uint16_t cmd_extract(char *s_input, uint16_t argc_max, char* argv[]) {
    uint8_t space_count = 0;
    uint8_t arg_number = 0;
    uint8_t char_number = 0;

    for (uint16_t i = 0; i < strlen(s_input); i++) {
        if (s_input[i] == " ") {
            if (++space_count > MAX_SPACES) {
                return arg_number-1;
            }
            arg_number++;
            char_number = 0;
        } else {
            argv[arg_number][char_number] = s_input[i];
            char_number++;
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
