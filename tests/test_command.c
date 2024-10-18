/** 
 * @file test_command.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-10-18
 * @brief Tests for the command module
 */


#include <stdint.h>
#include <stdbool.h>


#include "unity.h"

#include "fff.h"
DEFINE_FFF_GLOBALS;
#define FFF_MOCK_IMPL

#include "clear_mock.h"
#include "help_mock.h"
#include "IO_mock.h"
#include "led_mock.h"

#include "inc/command.h"

void reset_fff(void) {
    
}

void setUp(void) {
   
}

void tearDown(void) {
   
}

// =========================== Tests ===========================
void test_cmd_check_input_true(void) {
    TEST_ASSERT_EQUAL_MESSAGE(cmd_check_input("hello"), 1, "Command should have been correct");
}
