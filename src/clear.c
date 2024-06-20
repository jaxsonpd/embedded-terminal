/** 
 * @file clear.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-04-06
 * @brief A module to clear the terminals screen
 */


#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#include "lib/UART.h"

#include "inc/clear.h"

#define TERM_CLEAR "\033[2J\033[H\033[3J" // The VT100 clear screen command

int32_t clear_entry(uint16_t UNUSED(argc), char *UNUSED(argv[])) {
    printf(TERM_CLEAR);

    return 0;
}



