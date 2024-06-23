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

#include "inc/IO.h"

const char *g_usage = ":p:s:rh";

/** 
 * @brief Print the help text for the IO module
 * 
 */
void print_help(void) {
    printf("IO controller v0.1\r\n");
    printf("Help Text:\r\n");
    printf("This module is used to control all the IO on the device. It allows for\r\n");
    printf("both digital reads and writes.\r\n");
    printf("\r\n");
    printf("Flags:\r\n");
    printf("-p [pin number(1-13)]:\r\n");
    printf("    This flag controls what pin to use with the required argument.\r\n");
    printf("-s [value (0-1)]:\r\n");
    printf("    This flag is used to set the pin (digital write) and requires -p.\r\n");
    printf("-r:\r\n");
    printf("    Perform a digital read of the pin and print the output, requires -p.\r\n");
    printf("-h:\r\n");
    printf("    Print this text.\r\n");
    printf("\r\n");
    printf("Examples:\r\n");
    printf("    Digital Write: IO -p 13 -s 1\r\n");
    printf("    Digital Read: IO -p 3 -r\r\n");
}


/** 
 * @brief Perform a digital write
 * @param pin the pin to write to
 * @param state the state to write
 * 
 * @return 0 if successful
 */
uint8_t perform_digital_write(uint8_t pin , bool state) {
    if (pin > )
}


int32_t IO_entry(uint16_t argc, char *argv[]) {
    int16_t opt;
    bool s_flag = false, r_flag = false, p_flag = false, h_flag = false;


    opterr = false;


    while ((opt = getopt(argc, argv, g_usage)) != -1) {
        printf("result: %c\r\n", (char)opt);
        switch (opt) {
            case 'p':
                p_flag = 1;
                printf("Arg: %s\r\n", optarg);
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
            case ':':
                printf("%c missing required argument\r\n", optopt);
            default: // ? or :
                printf("Usage %s [-p pin] [-s output] [-r] [-h]\r\n", argv[0]);
                return EXIT_FAILURE;
                break;
        }
    }

    printf("p: %1d, s: %1d, r: %1d, h: %1d\r\n", p_flag, s_flag, r_flag, h_flag);

    if ((p_flag) && (!s_flag && !r_flag)) { // Require the other arguments
        printf("-p requires ether -s or -r\r\n");
        return EXIT_FAILURE;
    }

    if ((s_flag || r_flag) && (!p_flag)) {
        printf("-s or -r requires -p\r\n");
        return EXIT_FAILURE;
    }

    if (h_flag) {
        print_help();
    }
    



    return EXIT_SUCCESS;
}
