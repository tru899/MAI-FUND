#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "../include/funcs.h"
#include "../include/return_codes.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        err_status(INVALID_INPUT);
        return INVALID_INPUT;
    }

    char *x_str = argv[1];
    char *flag = argv[2];

    int x;
    return_codes status;

    status = str_to_int(x_str, &x);
    if (status != OK) {
        err_status(status);
        return status;
    }

    status = is_flag(flag);
    if (status != OK) {
        err_status(status);
        return status;
    }

    char f = flag[1];
    int res;
    unsigned long long res_ull;
    long long res_ll;
    char buf[256];
    int multiples[100];
    int count;
    long long table[10][10] = {0};

    switch (f) {
        case 'h':
            status = is_natural(x, &res, multiples, &count);
            if (status != OK) {
                err_status(status);
                return status;
            }
            print_natural(x, multiples, count);
            return status;
        case 'p':
            status = is_prime(x ,&res);
            if (status != OK) {
                err_status(status);
                return status;
            }
            if (res == -1)
                printf("%d — not prime, not composite\n", x);
            else if (res == 1)
                printf("%d — prime\n", x);
            else
                printf("%d — composite\n", x);
            return status;
        case 's':
            status = to_hex(x, buf);
            if (status != OK) {
                err_status(status);
                return status;
            }
            printf("%d to hex: %s\n", x, buf);
            return status;
        case 'e':
            status = power_table(x, table);
            if (status != OK) {
                err_status(status);
                return status;
            }
            print_table(x, table);
            return status;
        case 'a':
            status = sum_natural(x, &res_ull);
            if (status != OK) {
                err_status(status);
                return status;
            }
            printf("summa: %lld\n", res_ull);
            return status; 
        case 'f':
            status = factorial(x, &res_ll);
            if (status != OK) {
                err_status(status);
                return status;
            }
            printf("factorial of %d = %lld\n", x, res_ll);
            return status;
        default:
            err_status(UNKNOWN_FLAG);
            return UNKNOWN_FLAG;
        }
    return OK;
}