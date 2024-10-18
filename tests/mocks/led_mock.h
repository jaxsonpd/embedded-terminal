#include <stdbool.h>
#include <stdint.h>

#include "fff.h"

#include "inc/led.h"


#ifdef FFF_MOCK_IMPL
#define VOID_FUNC FAKE_VOID_FUNC
#define VALUE_FUNC FAKE_VALUE_FUNC
#else
#define VOID_FUNC DECLARE_FAKE_VOID_FUNC
#define VALUE_FUNC DECLARE_FAKE_VALUE_FUNC
#endif

#define FFF_LED_FAKES_LIST(FUNC) \
    FUNC(led_entry)

VALUE_FUNC(int32_t, led_entry, uint16_t, char **)