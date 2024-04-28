/** 
 * @file clear.h
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-04-06
 * @brief A module to clear the terminals screen
 */


#ifndef CLEAR_H
#define CLEAR_H


#include <stdint.h>
#include <stdbool.h>

/** 
 * @brief The entry point for the clear screen command which 
 * 
 * clears the terminal using the VT100 clear command    
 * @param args the arguments for the command    
 * 
 * @return the result of excuting the command
 */
uint8_t clear_entry(char *args);


#endif // CLEAR_H