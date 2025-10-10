#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>

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
        case ERROR_ALLOC:
            printf("error: alloc\n");
            return;
        case INVALID_BASE:
            printf("error: invalid base\n");
            return;
		case UNKNOWN_FLAG:
			printf("error: unknown flag\n");
			return;
	}
	return;
}

char* dec_to_base(long long val, int base) {
    int buf = 64;
    char *res = malloc(buf * sizeof(char));
    if (res == NULL) {
        return NULL;
    }

    if (val == 0) {
        res[0] = '0';
        res[1] = '\0';
        return res;
    }

    int sign = 1;
    if (val < 0) {
        sign = -1;
        val *= sign;
    }

    const char *digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    int i = 0;
    while (val != 0) {
        int ost = val % base;
        res[i] = digits[ost];
        i++;
        val /= base;
    }
    if (sign == -1) {
        res[i] = '-';
        i++;
    }
    res[i] = '\0';

    for (int j = 0; j < i / 2; j++) {
        char tmp = res[j];
        res[j] = res[i - j - 1];
        res[i - j - 1] = tmp;
    }
    return res;
}
