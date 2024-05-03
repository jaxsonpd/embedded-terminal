/** 
 * @file clear.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-04-06
 * @brief A module to clear the terminals screen
 */


#include <stdint.h>
#include <stdbool.h>

#include "include/UART.h"

#include "clear.h"

#define TERM_CLEAR "\033[2J\033[H\033[3J" // The VT100 clear screen command

uint8_t clear_entry(uint16_t argc, char **argv) {
    printf(TERM_CLEAR);

    return 0;
}



