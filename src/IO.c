/** 
 * @file IO.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-05-04
 * @brief The implementation of the IO module which allow the user to control the IO ports
 */


#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

#include "utils.h"

#include "IO.h"

const char *g_usage = ":p:s:rh";


int32_t IO_entry(uint16_t argc, char *argv[]) {
    int16_t opt;
    bool s_flag = false, r_flag = false, p_flag = false, h_flag = false;


    opterr = false;


    while ((opt = getopt(argc, argv, g_usage)) != -1) {
        switch (opt) {
            case 'p':
                p_flag = 1;
                break;
            case 's': // Set mode
                s_flag = 1;
                break;
            case 'r':
                r_flag = 1;
                break;
            case 'h':
                h_flag = 1;
                break;
            default: // ? or :
                fprintf(stderr, "Usage %s [-p pin] [-s output] [-r] [-h]\n", argv[0]);
                return EXIT_FAILURE;
                break;
        }
    }

    printf("p: %1d, s: %1d, r: %1d, h: %1d\n", p_flag, s_flag, r_flag, h_flag);

    if ((p_flag) & (!s_flag & !r_flag)) { // Require the other arguments
        printf("-p requires ether -s or -r\n");
        return EXIT_FAILURE;
    }
    
    return EXIT_SUCCESS;
}
