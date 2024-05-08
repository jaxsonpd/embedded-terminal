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

#include "utils.h"


uint8_t utils_get_line (char *prmpt, char *buffer, size_t buffSize) {
    bool extra;
    char ch;

    if (prmpt != NULL) {
        printf("%s", prmpt);
        fflush (stdout); // not required
    }

    if (fgets (buffer, buffSize, stdin) == NULL) {
        return 1;
    }

    if (buffer[strlen(buffer)-1] != '\n') {
        extra = false;
        while (((ch = getchar()) != '\n') && (ch != EOF))
            extra = true;
        return (extra == true) ? 2 : 0;
    }

    return 0;
}


uint8_t utils_get_line_echo (char *prmpt, char *buffer, size_t buffSize) {
    
    if (prmpt != NULL) {
        printf("%s", prmpt);
        fflush (stdout); // not required
    }

    size_t index = 0;
    int8_t c;

    // Get input
    while (((c = fgetc(stdin)) != EOF) && (c != '\n') && (c != '\r') && (index < buffSize - 1)) {
        if (c == 0x08) { // Backspace
            buffer[index--] = '\0';
        } else {
            buffer[index++] = (char)c;   
        }
        printf("%c", c);
    }

    if (((c == '\n') || (c == '\r')) && (index < buffSize - 1)) {
        buffer[index++] = '\n';
        printf("\r\n");
    }

    buffer[index] = '\0';

    return 0;
}

/// @brief The options argument string 
char *optarg; 

/// @brief The index of the next element to be processed in argv
int16_t optind=1;

/// @brief If this is set to zero then no error messages are printed by getopt()
int16_t opterr=1;

/// @brief Where an error option is placed
char optopt;


int16_t getopt (int argc, char* argv[], char *optstring) {
    bool isopt = false;
    bool reqarg = false;
    bool reqargopt = false;

    char* opt = argv[optind];

    printf("opt: %s\n", opt);

    // Check to see if opt should be processed
    if (optind >= argc) {
        optind = 1;
        return -1;
    }

    if (opt[0] == '-') { // it is an option
        for (uint16_t i = 0; i <= strlen(optstring); i++) {
            if (optstring[i] == opt[1]) {
                if (optstring[i+1] == ':') {
                    if (optstring[i+2] == ':') reqargopt = true;
                    else reqarg = true;
                }
                isopt = true;
                break;
            }
        }
    } else { // Technically should permute through here but for now ignore and move on
        optind++;
        return getopt(argc, argv, optstring);
    }

    // Process opt
    if (!isopt) {
        optopt = argv[optind][1];
        optind++;
        // need to include printing error message
        return '?';

    } else if (reqarg) {
        if ((optind != argc) && (argv[optind+1][0] != '-')) { // There is an argument
            optarg = argv[optind+1];
            optind += 2;
            
            return opt[1];
        } else {
            optind++;
            optopt = opt;

            return ':';
        }

    } else if (reqargopt) {
        if ((optind != argc) && (argv[optind+1][0] != '-')) { // There is an argument
            optarg = argv[optind+1];
            optind += 2;
        } else {
            optind++;
        }

        return opt[1];
    } else {

        optind++;
        return opt[1];
    }
}


