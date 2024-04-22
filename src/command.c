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


CMDs_t *CMD_setup(void) {
    CMDs_t *p_commands = calloc(1, sizeof(CMDs_t));

    // inilise the commands
    CMD_t help = {
        .name = "help",
        .command = HELP_entry
    };

    CMD_t clear = {
        .name = "clear",
        .command = CLR_entry
    };

    CMD_t led = {
        .name = "led",
        .command = LED_entry
    };

    p_commands->list = calloc(NUM_CMDS, sizeof(CMD_t));
    p_commands->list[0] = help;
    p_commands->list[1] = clear;
    p_commands->list[2] = led;

    p_commands->length = NUM_CMDS;

    return p_commands;
}


void CMD_execute(CMDs_t commands, char *cmd, char *args) {
    for (uint8_t i=0; i < commands.length; i++) {
        if (strcmp(commands.list[i].name, cmd) == 0) {
            commands.list[i].command(args);
        }
    }
}

void CMD_extract(char *p_input, uint16_t inputSize, char *p_cmd, uint16_t maxCMDLength, 
                char *p_args, uint16_t maxArgsLength) {
    char c = 0;
    uint16_t cmdIndex = 0;
    uint16_t argsIndex = 0;
    bool inCMD = true;

    for (uint16_t i = 0; i < inputSize; i++) {
        c = p_input[i];

        // proccess command
        if (inCMD && (c == ' ')) { // CMD is over
            inCMD = false;
        } else if (c == '\n') { // input is over
            break;
        } else if (inCMD) {
            p_cmd[cmdIndex++] = c;
        } else {
            p_args[argsIndex++] = c;
        }

        // Check sizing
        if (cmdIndex >= maxCMDLength-1) { // cut off the command
            inCMD = false;
        }

        if (argsIndex >= maxArgsLength-1) { // cut off cmd and args interpretation
            break;
        }
    }    

    p_args[argsIndex] = '\0';
    p_cmd[cmdIndex] = '\0';
}



bool CMD_checkInput(char *cmd) {

    return 1;
}

void CMD_printError(char *p_cmd) {
    printf("%s is not a valid cmd please try again \n \n", p_cmd);
}
