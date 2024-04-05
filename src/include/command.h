/** 
 * @file command.h
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-03-31
 * @brief The header for the command module
 */


#ifndef COMMAND_H
#define COMMAND_H


#include <stdint.h>
#include <stdbool.h>

/** 
 * @struct CMD_t
 *  A structure used for storing a command
 * 
 * @var CMD_t::name
 *  The name of the command
 * @var CMD_t::command
 *  A pointer to the entry function for the command
 * 
 */
typedef struct {
    char *name; 
    uint8_t (*command)(char *); 
} CMD_t;


/** 
 * @struct CMDs_t
 *  A structure used for storing a array of commands 
 * 
 * @var CMD_t::list
 *  The array of commands
 * @var CMD_t::length
 *  The number of commands
 * 
 */
typedef struct {
    CMD_t *list;
    uint8_t length;
} CMDs_t;

/** 
 * @brief excute the command with the give arguments
 * @param commands an array of commands that are available
 * @param cmd a pointer to the command string
 * @param args a pointer to the arguments string
 */
void CMD_execute(CMDs_t commands, char *cmd, char *args);


/** 
 * @brief exctract the command from an input buffer
 * @param p_input a pointer to the input string
 * @param inputSize the size of the input string
 * @param p_cmd a pointer to the command string
 * @param maxCMDLength the size of the command string
 * @param p_args a pointer to the args string
 * @param maxArgsLength the size of the args string
 * 
 */
void CMD_extract(char *p_input, uint16_t inputSize, char *p_cmd, uint16_t maxCMDLength,
                char *p_args, uint16_t maxArgsLength);


/** 
 * @brief check if the inputed command is an excutable
 * @param cmd the command to check
 * 
 * @return 1 if excutable 0 otherwise
 */
bool CMD_checkInput(char *cmd);


/** 
 * @brief print an error as the given command is not an excutable
 * @param p_cmd the command that is not excutable
 * 
 */
void CMD_printError(char *p_cmd);

#endif // COMMAND_H
