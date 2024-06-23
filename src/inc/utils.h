/** 
 * @file utils.h
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-04-22
 * @brief various utility functions
 */


#ifndef UTILS_H
#define UTILS_H


#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

#ifdef __GNUC__
/**
 * @brief This macro is used to tell gcc that the function parameter is unused.
 * 
 * This can be used like so: void foo(int UNUSED(bar));
 * This will only work on gcc and clang.
 * 
 * @param x the attribute that is unused
 */
#  define UNUSED(x) UNUSED_ ## x __attribute__((__unused__))
#else
#  define UNUSED(x) UNUSED_ ## x
#endif

#ifdef __GNUC__
/**
 * @brief This macro is used to tell gcc that the function is unused.
 * 
 * This can be used like so: void UNUSED_FUNCTION(foo)(int UNUSED(bar));
 * This will only work on gcc and clang.
 * 
 * @param x the function that is unused
 */
#  define UNUSED_FUNCTION(x) __attribute__((__unused__)) UNUSED_ ## x
#else
#  define UNUSED_FUNCTION(x) UNUSED_ ## x
#endif

/** 
 * @brief read a line from stdin
 * @param prmpt the prompt to place at the begining
 * @param buffer the buffer to place the read line into
 * @param bufferSize the size of the input buffer
 * 
 * @return 0 if succesful 1 if no input 2 if input is to long
 */
uint8_t utils_get_line (char *prmpt, char *buffer, size_t buffSize);


/** 
 * @brief read a line from stdin but echo each character back if a \n or \r 
 *        is recived it is put into the input string as \n and \n\r is printed
 * @param prmpt the prompt to place before the input
 * @param buffer the char buffer to place the input into
 * @param bufSize the max buffer size
 * 
 * @return 0 if succesful
 */
uint8_t utils_get_line_echo (char *prmpt, char *buffer, size_t buffSize);

/// @brief The options argument string 
extern char *optarg; 

/// @brief The index of the next element to be processed in argv
extern int16_t optind;

/// @brief If this is set to zero then no error messages are printed by getopt()
extern int16_t opterr;

/// @brief Where an error option is placed
extern char optopt;

/** 
 * @brief Get the options from a list of command line options.
 *  
 * This implementation is based on the GNU implementation of getopt() as often defined in <unistd.h>
 * 
 * @cite https://man7.org/linux/man-pages/man3/getopt.3.html
 * @related optarg, optind, opterr, optopt
 * 
 * @param argc the number of arguments passed
 * @param argv the list of each argument passed
 * @param optstring the string that defines the available options
 * 
 * @return successively each option character and -1 at end, '?' is returned when an option is not recognised and ':' 
 * returned when a required argument is not provided
 */
int16_t getopt (int argc, char* argv[], const char *optstring);



#endif // UTILS_H