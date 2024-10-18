/** 
 * @file test_getopt.c
 * @author Jack Duignan (JackpDuignan@gmail.com)
 * @date 2024-10-18
 * @brief Test the getopt function used to process command line arguments
 */


#include <stdint.h>
#include <stdbool.h>

#include "unity.h"
#include "inc/utils.h"

#include "fff.h"
DEFINE_FFF_GLOBALS;
#define FFF_MOCK_IMPL

void setUp(void) {
    
}

void tearDown(void) {

}

// =========================== Tests ===========================
void test_getopt_success(void) {
    TEST_ASSERT_TRUE(true);
}
