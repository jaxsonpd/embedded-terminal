/** 
 * @file test.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-05-08
 * @brief This file is used for testing things needed in the project without re writing files
 */


#include <stdint.h>
#include <stdbool.h>

#include <util/delay.h>
#include <stdio.h>

#include "../src/include/UART.h"


int main(void) {
    UART_init_stdio(57600);

    while (1) {
        _delay_ms(100);
        printf("Hello World\r\n");
    }
}