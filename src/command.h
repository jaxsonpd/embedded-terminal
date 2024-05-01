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
 * @brief Initialise the commands
 * 
 * @return a pointer to the command list struct
 */
CMDs_t *cmd_init(void);


/** 
 * @brief Execute the command with the give arguments
 * 
 * @param commands an array of commands that are available
 * @param cmd a pointer to the command string
 * @param args a pointer to the arguments string
 */
void cmd_execute(CMDs_t commands, char *cmd, char *args);


/** 
 * @brief Extract the command from an input buffer
 * 
 * @param s_input the input string
 * @param argc_max the maximum number of arguments
 * @param argv a pointer to the argv array of arguments to populate
 * 
 * @return the resulting length of argv
 */
uint16_t cmd_extract(char *s_input, uint16_t argc_max, char* argv[]);


/** 
 * @brief check if the inputted command is an executable
 * 
 * @param cmd the command to check
 * 
 * @return 1 if executable 0 otherwise
 */
bool cmd_check_input(char *cmd);


/** 
 * @brief print an error as the given command is not an executable
 * @param p_cmd the command that is not executable
 * 
 */
void cmd_print_error(char *p_cmd);

#endif // COMMAND_H
