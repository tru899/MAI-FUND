#pragma once
#include <stddef.h>

typedef enum return_codes {
    OK = 0,
    INVALID_INPUT,
    ERROR_OVERFLOW,
    ERROR_NULL,
    ERROR_OPEN_FILE,
    INVALID_BASE,
    INVALID_SEPARATOR,
    UNKNOWN_FLAG
} return_codes;
