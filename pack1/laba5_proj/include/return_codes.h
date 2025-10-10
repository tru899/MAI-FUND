#pragma once
#include <stddef.h>

typedef enum return_codes {
    OK = 0,
    INVALID_INPUT,
    ERROR_OVERFLOW,
    ERROR_NULL,
    ERROR_ALLOC,
    UNKNOWN_FLAG
} return_codes;
