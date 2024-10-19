/**
 * @file utils.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-04-22
 * @brief A collection of utilities that clutter the main file
 */


#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "inc/utils.h"


uint8_t utils_get_line(char* prmpt, char* buffer, size_t buffSize) {
    bool extra;
    char ch;

    if (prmpt != NULL) {
        printf("%s", prmpt);
        fflush(stdout); // not required
    }

    if (fgets(buffer, buffSize, stdin) == NULL) {
        return 1;
    }

    if (buffer[strlen(buffer) - 1] != '\n') {
        extra = false;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = true;
        return (extra == true) ? 2 : 0;
    }

    return 0;
}


uint8_t utils_get_line_echo(char* prmpt, char* buffer, size_t buffSize) {

    if (prmpt != NULL) {
        printf("%s", prmpt);
        fflush(stdout); // not required
    }

    size_t index = 0;
    int8_t c;

    // Get input
    while (((c = fgetc(stdin)) != EOF) && (c != '\n') && (c != '\r') && (index < buffSize - 1)) {
        if ((c == 0x7F) || (c == 0x08)) { // Backspace
            index--;
            printf("%c", 0x7F);
        } else {
            buffer[index++] = (char)c;
            printf("%c", c);
        }

    }

    if (((c == '\n') || (c == '\r')) && (index < buffSize - 1)) {
        buffer[index++] = '\n';
        printf("\r\n");
    }

    buffer[index] = '\0';

    return 0;
}

/// @brief The options argument string 
char* optarg;

/// @brief The index of the next element to be processed in argv
int16_t optind = 1;

/// @brief If this is set to zero then no error messages are printed by getopt()
int16_t opterr = 1;

/// @brief Where an error option is placed
char optopt;

/// @brief What type is the option currently being processed
typedef enum option_type {
    NOT_AN_OPTION,
    ERROR_OPTION,
    SINGLE_OPTION,
    REQURED_ARGUMENT,
    OPTIONAL_ARGUMENT
} option_t;

/**
 * @brief Find what type of option has been provided
 * @param option the option to test
 * @param option_string the option string for the process
 *
 * @return what type of option it is REQUIRED_ARGUMENT etc.
 */
option_t find_option_type(char* option, const char* option_string) {
    option_t r_type;

    if (option[0] != '-') {
        r_type = NOT_AN_OPTION;
        return r_type;
    }

    for (uint16_t i = 0; i < strlen(option_string); i++) {
        if (option_string[i] == option[1]) {
            if (i < (strlen(option_string) - 1) && option_string[i + 1] == ':') {
                if (i < (strlen(option_string) - 2) && option_string[i + 2] == ':') {
                    r_type = OPTIONAL_ARGUMENT;
                } else {
                    r_type = REQURED_ARGUMENT;
                }
            } else {
                r_type = SINGLE_OPTION;
            }

            return r_type;
        }
    }

    r_type = ERROR_OPTION; // Option has not been found in option_string
    return r_type;
}



int16_t getopt(int argc, char* argv[], const char* optstring) {
    char* option = argv[optind];

    // Check to see if opt should be processed
    if (optind >= argc) {
        optind = 1;
        return -1;
    }

    // Find the option type
    option_t option_type = find_option_type(option, optstring);

    if (option_type == NOT_AN_OPTION) {
        optind++;
        return getopt(argc, argv, optstring);
    }

    // Process opt
    if (option_type == ERROR_OPTION) {
        optopt = option[1];
        optind++;
        if (!opterr) {
            fprintf(stderr, "Error argument, usage: %s\r\n", optstring);
        }
        return '?';

    } else if (option_type == REQURED_ARGUMENT) {
        if ((optind != argc) && (argv[optind + 1][0] != '-')) { // There is an argument
            optarg = argv[optind + 1];
            optind += 2;

            return option[1];
        } else {
            optind++;
            optopt = option[1];

            return ':';
        }

    } else if (option_type == OPTIONAL_ARGUMENT) {
        if ((optind != argc) && (argv[optind + 1][0] != '-')) { // There is an argument
            optarg = argv[optind + 1];
            optind += 2;
        } else {
            optind++;
        }

        return option[1];

    } else {
        optind++;
        return option[1];
    }
}


