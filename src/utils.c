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


uint8_t UTL_getLine (char *prmpt, char *buffer, size_t buffSize) {
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
