#pragma once
#include <stddef.h>

typedef enum return_codes {
    OK = 0,
    INVALID_INPUT,
    ERROR_OVERFLOW,
    NO_MULTIPLES,
    ERROR_NULL,
    ERROR_ALLOC,
    UNKNOWN_FLAG
} return_codes;

typedef enum solution_codes {
    NO_SOLUTIONS,
    ONE_SOLUTION,
    TWO_SOLUTIONS,
    INFINITE_SOLUTIONS
} solution_codes;
