/** 
 * @file command.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-03-31
 * @brief This file handles command registration and excution
 */


#include <stdint.h>
#include <stdbool.h>

#include "command.h"
#include "UART.h"


void CMD_execute(char* p_cmd, char* p_args) {
    UART_puts("Excuted: ");
    UART_puts(p_cmd);
    UART_puts(" With args: ");
    UART_puts(p_args);
    UART_puts("\n");
}


void CMD_extract(char* p_input, uint16_t inputSize, char* p_cmd, uint16_t maxCMDLength, 
                char* p_args, uint16_t maxArgsLength) {
    char c = 0;
    uint16_t cmdIndex = 0;
    uint16_t argsIndex = 0;
    bool inCMD = true;

    for (uint16_t i = 0; i < inputSize; i++) {
        c = p_input[i];

        // proccess comand
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

        if (argsIndex >= maxArgsLength-1) { // cut off cmd and args interperitation
            i = inputSize;
        }
    }    

    p_args[argsIndex] = '\0';
    p_cmd[cmdIndex] = '\0';
}


bool CMD_checkInput(char* cmd) {

    return 1;
}

void CMD_printError(char* p_cmd) {
    UART_puts(p_cmd);
    UART_puts(" is not a valid cmd please try again \n \n");
}
