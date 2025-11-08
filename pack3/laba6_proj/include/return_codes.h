#pragma once
#include <stddef.h>

typedef enum return_codes {
    OK = 0,
    INVALID_INPUT,
    INVALID_BASE,
    ERROR_OVERFLOW,
    NO_MULTIPLES,
    ERROR_ALLOC,
    INVALID_PATH,
    WRONG_BRACKETS,
    EMPTY_STACK,
    UNKNOWN_FLAG
} return_codes;
