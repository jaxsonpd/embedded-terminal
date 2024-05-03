/** 
 * @file IO.h
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-05-04
 * @brief The declaration of the IO module which allows the user to control the IO ports on there controller
 */


#ifndef IO_H
#define IO_H


#include <stdint.h>
#include <stdbool.h>


/** 
 * @brief The entry point into the IO module
 * @param argc the number of arguments passed
 * @param argv the array of arguments
 * 
 * @return 0 for successes
 */
uint8_t IO_entry(uint16_t argc, char *argv[]);



#endif // IO_H