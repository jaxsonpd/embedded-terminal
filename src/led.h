/** 
 * @file led.h
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-04-09
 * @brief A module to control an led
 */


#ifndef LED_H
#define LED_H


#include <stdint.h>
#include <stdbool.h>

/** 
 * @brief The entry point for the led command
 * @param args the argument string
 * 
 * @return 0 if succesful
 */
uint8_t led_entry(char *args);



#endif // LED_H