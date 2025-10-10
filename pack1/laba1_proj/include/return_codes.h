#pragma once
#include <stddef.h>

typedef enum return_codes {
    OK = 0,
    INVALID_INPUT,
    ERROR_OVERFLOW,
    NO_MULTIPLES,
    UNKNOWN_FLAG
} return_codes;
