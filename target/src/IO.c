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

#include "GPIO.h"

#include "inc/IO.h"

const char g_usage[] = ":p:s:rh";

/**
 * @brief Print the help text for the IO module
 *
 */
static void print_help(void) {
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
    printf("    Digital Write: IO -p B5 -s 1\r\n");
    printf("    Digital Read: IO -p 3 -r\r\n");
}


/**
 * @brief Perform a digital write
 * @param port the port to write to
 * @param pin_num the pin to write to
 * @param state the state to write
 *
 * @return 0 if successful
 */
static uint8_t perform_digital_write(char port, char pin_num, char state) {
    int8_t pin_int = (int8_t)(pin_num)-48;
    int8_t state_int = (int8_t)(state)-48;

    if (port != 'B' && port != 'D' && port != 'C') {
        printf("%c is not a valid port.\r\n", port);
        return 1;
    }

    if (pin_int < 0 || pin_int > 10) {
        printf("%d is not a valid pin number.\r\n", pin_num);
        return 1;
    }

    if (state_int != 0 && state_int != 1) {
        printf("%c is not a valid state.\r\n", state);
        return 1;
    }

    pin_t pin = PIN(port, pin);

    GPIO_pin_init(pin, OUTPUT);

    GPIO_set_output(pin, state_int);

    return 0;
}


int32_t IO_entry(uint16_t argc, char* argv[]) {
    int16_t opt;
    bool s_flag = false, r_flag = false, p_flag = false, h_flag = false;

    opterr = false;

    char* port;
    char state;

    while ((opt = getopt(argc, argv, g_usage)) != -1) {
        printf("result: %c\r\n", (char)opt);
        switch (opt) {
        case 'p':
            p_flag = 1;
            printf("Arg: %s\r\n", optarg);
            port = optarg;
            break;
        case 's': // Set mode
            s_flag = 1;
            printf("Arg: %s\r\n", optarg);
            state = optarg[0];
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

    if (s_flag && p_flag) {
        if (perform_digital_write(port[0], port[1], state) == 0) {
            printf("Set: %s to %d.\r\n", port, (int8_t)state - 48);
        }
    }

    return EXIT_SUCCESS;
}
