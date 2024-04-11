/** 
 * @file led.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-04-09
 * @brief A module to switch on the led connected to pin 13 on the arduino (PortB pin 5)
 * 
 * This module just uses direct address communication and will be re writen once the GPIO driver is up and running  
 */


#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include <avr/io.h>

#include "include/UART.h"

#include "led.h"


/** 
 * @brief initalise the pin to be an output
 * 
 * @return true if succesful
 */
static bool init(void) {
    DDRB |= 1 << DDB5; // Set the pin to output

    return true;
}

uint8_t LED_entry(char *args) {
    if (!init()) {
        UART_puts("LED initalisation failed please check configuration.\n");
    }

    if (strcmp(args, "on") == 0) {
        UART_puts("LED on\n");  
        PORTB |= 1 << PORTB5; // set pin high
    } else {
        UART_puts("LED off\n");
        PORTB &= ~(1 << PORTB5); // set pin low
    }

    return 0;
}