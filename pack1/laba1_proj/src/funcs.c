#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include "../include/funcs.h"
#include "../include/return_codes.h"

int str_to_int(const char *str, int *out) {
    char *endptr;
    long val = strtol(str, &endptr, 10);

    if (val > INT_MAX || val < INT_MIN) {
        return ERROR_OVERFLOW;
    }
    if (endptr == str || *endptr != '\0') {
        return INVALID_INPUT;
    }

    *out = (int)val;
    return OK;
}

int is_flag(const char* flag) {
    if (strlen(flag) != 2) {
        return INVALID_INPUT;
    }
    if (flag[0] != '-' && flag[0] != '/') {
        return INVALID_INPUT;
    }
    char f = flag[1];
    switch(f) {
        case 'h':
        case 'p':
        case 's':
        case 'e':
        case 'a':
        case 'f':
            return OK;
        default:
            return UNKNOWN_FLAG;
    }
}

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
		case NO_MULTIPLES:
			printf("error: no multiplies\n");
			return;
		case UNKNOWN_FLAG:
			printf("error: unknown flag\n");
			return;
	}
	return;
}

int is_natural(int x, int *found_nat, int *multiplies, int *count) {
    *found_nat = 0;
    *count = 0;
    if (x > 0) {
        for (int i = 1; i <= 100; i++) {
            if (i % x == 0) {
                multiplies[*count] = i;
                (*count)++;
                *found_nat = 1;
            }
        }
    } else {
        return INVALID_INPUT;
    }
    if (*found_nat == 0) {
        return NO_MULTIPLES;
    }
    return OK;
}

int is_prime(int x, int *prime_flag) {
    if (x < 2) {
        *prime_flag = -1;
        return OK;

    } else if (x == 2) {
        *prime_flag = 1;
        return OK;
    } else if (x % 2 == 0) {
        *prime_flag = 0;
        return OK;
    } else {
        for (int i = 3; i <= (int)sqrt(x) + 1; i+=2) {
            if (x % i == 0) {
                *prime_flag = 0;
                return OK;
            }
        }
    }
    *prime_flag = 1;
    return OK;
}

int to_hex(int x, char *buf) {
    if (x < 0) {
        return INVALID_INPUT;
    }
    if (x == 0) {
        buf[0] = '0';
        buf[1] = '\0';
        return OK;
    }

    int base = 16;
    int r;
    char tmp[32];
    char *p = tmp + 31;
    *p-- = '\0';

    while (x) {
        r = x % base;
        if (r > 9) {
            *p-- = r - 10 + 'A';
        } else {
            *p-- = r + '0';
        }
        x /= base;
    }
    
    //for probels
    const char *src = p + 1;
    char *dst = buf;
    while (*src) {
        *dst++ = *src++;
        if (*src) {
            *dst++ = ' ';
        }
    }
    *dst = '\0';
    return OK;
}

int power_table(int x, long long table[10][10]) {
    if (x <= 0 || x > 10) {
        return INVALID_INPUT;
    } else {
        for (int i = 1; i <= x; i++) {
            for (int osn = 1; osn <= 10; osn++) {
                long long res = 1;
                for (int j = 0; j < i; j++) {
                    if (res > LLONG_MAX / osn) {
                        return ERROR_OVERFLOW;
                    }
                    res *= osn;
                }
                table[i - 1][osn - 1] = res;
            }
        }
    }
    return OK;
}

int sum_natural(int x, unsigned long long *res) {
    if (x < 1) {
        return INVALID_INPUT;
    }

    *res = x * ((double)((x + 1) / 2));
    return OK;
}

int factorial(int x, long long *res) {
    if (x < 0) {
        return INVALID_INPUT;
    }
    *res = 1;
    for (int i = 1; i <= x; i++) {
        if (*res >= LLONG_MAX / i) {
            return ERROR_OVERFLOW;
        }
        *res *= i;
    }
    return OK;
}

void print_natural(int x, int *multiples, int count) {
    printf("multiples of %d:", x);
    for (int i = 0; i < count; i++) {
        printf(" %d", multiples[i]);
    }
    printf("\n");
}

void print_table(int x, long long table[10][10]) {
    for (int i = 0; i < x; i++) {
        for (int osn = 0; osn < 10; osn++) {
            printf("%2d^%-2d=%-12lld", osn + 1, i + 1, table[i][osn]);
        }
        printf("\n");
    }
}