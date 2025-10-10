#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "../include/funcs.h"
#include "../include/return_codes.h"

void err_status(return_codes status) {
	switch (status) {
		case OK:
			printf("ok :)\n");
			return;
		case INVALID_INPUT:
			printf("error: invalid input\n");
			return;
		case ERROR_OVERFLOW:
			printf("error: overflow\n");
			return;
        case ERROR_NULL:
            printf("error: null\n");
            return;
        case INVALID_BASE:
            printf("error: invalid base\n");
            return;
        case ERROR_OPEN_FILE:
            printf("error: can't open the file\n");
            return;
        case INVALID_SEPARATOR:
            printf("error: invalid separator\n");
            return;
		case UNKNOWN_FLAG:
			printf("error: unknown flag\n");
			return;
	}
	return;
}

int get_base(const char* num_str) {
    int min_base = 2;
    for (int i = 0; num_str[i]; i++) {
        char c = toupper((unsigned char)num_str[i]);
        int digit;
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            digit = c - 'A' + 10;
        } else {
            return INVALID_INPUT;
        }
        if (digit >= min_base) {
            min_base = digit + 1;
        }
    }
    if (min_base <= 36) {
        return min_base;
    } else {
        return INVALID_BASE;
    }
}

long long to_dec(const char* num_str, int base) {
    long long res = 0;
    int len = strlen(num_str);
    for (int i = 0; i < len; ++i) {
        char c = toupper((unsigned char)num_str[i]);
        int digit;
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            digit = c - 'A' + 10;
        } else {
            return INVALID_INPUT;
        }

        if (digit >= base) {
            return INVALID_BASE;
        }
        if (res > (LLONG_MAX - digit) / base) {
            return ERROR_OVERFLOW;
        }
        res = res * base + digit;
    }
    return res;
}

int is_space(char str) {
    return (str == ' ' || str == '\t' || str == '\n');
}
