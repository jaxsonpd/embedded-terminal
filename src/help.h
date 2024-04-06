/** 
 * @file help.h
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-04-06
 * @brief The help command module
 */


#ifndef HELP_H
#define HELP_H


#include <stdint.h>
#include <stdbool.h>

/** 
 * @brief Exucte the help command with the given arguments
 * @param args the array of args
 * 
 * @return the status of the command
 */
uint8_t HELP_entry(char* args);


#endif // HELP_H