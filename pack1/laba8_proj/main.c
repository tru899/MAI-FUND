#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "../include/funcs.h"
#include "../include/return_codes.h"

int main() {
    int base;
    return_codes status = OK;

    if (scanf("%d", &base) != 1) {
        err_status(INVALID_BASE);
        return INVALID_BASE;
    }
    if (base < 2 || base > 36) {
        err_status(INVALID_BASE);
        return INVALID_BASE;
    }

    char buf[256];
    long long max_val = 0;
    int first_val_flag = 1;

    while (1) {
        if (scanf("%255s", buf) != 1) {
            err_status(INVALID_INPUT);
            return INVALID_INPUT;
        }
        if (strcmp(buf, "Stop") == 0) {
            break;
        }
        int start = 0;
        int negative_flag = 0;

        if (buf[0] == '-') {
            start = 1;
            negative_flag = 1;
        }

        long long cur_val = 0;

        for (int i = start; buf[i] != '\0'; i++) {
            char c = toupper(buf[i]);
            int digit;

            if (c >= '0' && c <= '9') {
                digit = c - '0';
            } else {
                digit = c - 'A' + 10;
            }
            if (digit >= base) {
                err_status(INVALID_INPUT);
                return INVALID_INPUT;
            }
            if (negative_flag) {
                if (cur_val < (LLONG_MIN + digit) / base) {
                    err_status(ERROR_OVERFLOW);
                    return ERROR_OVERFLOW;
                }
                cur_val = cur_val * base - digit;
            } else {
                if (cur_val > (LLONG_MAX - digit) / base) {
                    err_status(ERROR_OVERFLOW);
                    return ERROR_OVERFLOW;
                }
                cur_val = cur_val * base + digit;
            }
        }

        if (first_val_flag || llabs(cur_val) > llabs(max_val)) {
            max_val = cur_val;
            first_val_flag = 0;
        }
    }

    if (first_val_flag) {
        err_status(INVALID_INPUT);
        return INVALID_INPUT;
    }

    int bases[] = {9, 18, 27, 36};
    for (int i = 0; i < 4; i++) {
        char *res = dec_to_base(max_val, bases[i]);
        if (res == NULL) {
            err_status(ERROR_ALLOC);
            return ERROR_ALLOC;
        }

        int j = 0;
        int is_minus = 0;

        if (res[0] == '-') {
            is_minus = 1;
            j = 1;
        }
        while (res[j] == '0' && res[j + 1] != '\0') {
            j++;
        }

        if (is_minus == 1) {
            printf("base: %d, num: -%s\n", bases[i], res + j);
        } else {
            printf("base: %d, num: %s\n", bases[i], res + j);
        }
        free(res);
    }
    return OK;
}
