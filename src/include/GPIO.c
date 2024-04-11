/** 
 * @file GPIO.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-04-07
 * @brief A library to control the GPIO on the microcontroller
 */


#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>

#include "GPIO.h"

void GPIO_pinInit(uint16_t pin, pinType_t type) {
    // Set the DDR and PORT to match the type
    volatile uint8_t *DDR_pin = PINBANK(pin) - 1; // DDRX is one regs lower then PORTX 
    
    if (type == OUTPUT) {
        *DDR_pin |= (1 << PINNUM(pin));
    } else if (type == INPUT_PULLUP) {
        *DDR_pin &= ~(1 << PINNUM(pin));
        *(uint8_t *)PINBANK(pin) &= (1 << PINNUM(pin)); // set pullup
    } else if (type == INPUT_NO_PULLUP) {
        *DDR_pin &= ~(1 << PINNUM(pin));
        *(uint8_t *)PINBANK(pin) &= ~(1 << PINNUM(pin)); // set pullup
    }
}


void GPIO_setOutput(uint16_t pin, bool value) {
    if (value) {
        *(uint8_t *)PINBANK(pin) &= (1 << PINNUM(pin));
    } else {
        *(uint8_t *)PINBANK(pin) &= ~(1 << PINNUM(pin));
    }
}


bool GPIO_toggleOutput(uint16_t pin) {
    return 0;
}

bool GPIO_getState(uint16_t pin) {
    return 0;
}