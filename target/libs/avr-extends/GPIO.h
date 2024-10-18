/**
 * @file GPIO.h
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-04-11
 * @brief A library to control the GPIO on the microcontroller
 */


#ifndef GPIO_H
#define GPIO_H


#include <stdint.h>
#include <stdbool.h>

#include <avr/io.h>

/// Define a pin for use in the GPIO functions should be assigned to a pin_t
#define PIN(bank, num) (((bank) << 8) | (num))

typedef uint16_t pin_t;

/// Extract the pins number
#define PINNUM(pin) (pin & 255) 

/// Extract the pins bank
#define PINBANK(pin) (pin >> 8) 


/// The different types of GPIO pins
typedef enum pin_types {
    OUTPUT,
    INPUT_NO_PULLUP,
    INPUT_PULLUP,
} pinType_t;


/**
 * @brief Initalise the pin
 * @param pin the pin defined using the PIN macro
 * @param type the pin type (OUTPUT, INPUT_NO_PULLUP, INPUT_PULLUP)
 *
 */
void GPIO_pin_init(uint16_t pin, pinType_t type);


/**
 * @brief Set a pins output state
 * @param pin the pin to set the output state for
 * @param value the output value
 */
void GPIO_set_output(uint16_t pin, bool value);


/**
 * @brief toggle the output of a pin
 * @param pin the pin to toggel the state of
 *
 * @return the state of the pin
 */
bool GPIO_toggle_output(uint16_t pin);


/**
 * @brief Get the current state of the pin
 * @param pin the pin to read the state of
 *
 * @return the state of the pin
 */
bool GPIO_getState(uint16_t pin);










#endif // GPIO_H