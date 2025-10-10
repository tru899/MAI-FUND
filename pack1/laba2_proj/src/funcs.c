#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>
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
        case ERROR_NULL:
            printf("error: null\n");
            return;
        case ERROR_ALLOC:
            printf("error: alloc\n");
            return;
		case UNKNOWN_FLAG:
			printf("error: unknown flag\n");
			return;
	}
	return;
}

int vvod(int count, int **arr_out) {
    if (count <= 0 || arr_out == NULL) {
        return INVALID_INPUT;
    }
    if ((size_t)count > SIZE_MAX / sizeof(int)) {
        return ERROR_OVERFLOW;
    }
    int *arr = malloc(sizeof(int) * count);
    if (arr == NULL) {
        return ERROR_ALLOC;
    }

    for (int i = 0; i < count; i++) {
        char buf[64];
        if (scanf("%63s", buf) != 1) {
            free(arr);
            return INVALID_INPUT;
        }

        int val;
        int status = str_to_int(buf, &val);
        if (status != OK || val <= 0) {
            free(arr);
            return status == OK ? INVALID_INPUT : status;
        }

        arr[i] = val;
    }

    *arr_out = arr;
    return OK;
}

int find_max_n(const int *arr, int len) {
    int max_n = arr[0];
    for (int i = 0; i < len; i++) {
        if (arr[i] > max_n) {
            max_n = arr[i];
        }
    }
    return max_n;
}

int is_prime(int n_max, int **prime_out) {
    if (n_max <= 0) {
        return INVALID_INPUT;
    }

    long double n = (long double)n_max;
    long double bound = 0;

    if (n < 6) {
        bound = 15;
    } else {
        bound = n * (log(n) + log(log(n)));
    }

    if (bound >= INT_MAX) {
        return ERROR_OVERFLOW;
    }
    
    int limit = (int)bound + 10;

    //eratosfen
    char *sieve = calloc(limit + 1, sizeof(char));
    if (!sieve) {
        return ERROR_ALLOC;
    }
    sieve[0] = sieve[1] = 1;
    for (int i = 2; i * i <= limit; i++) {
        if (sieve[i] == 0) {
            for (int k = (long long)i * i; k <= limit; k += i) {
                sieve[k] = 1;
            }
        }
    }

    int *primes = malloc(sizeof(int) * n_max);
    if (!primes) {
        free(sieve);
        return ERROR_ALLOC;
    }

    int count = 0;
    for (int i = 2; i <= limit && count < n_max; i++) {
        if (!sieve[i]) {
            primes[count++] = i;
        }
    }
    free(sieve);

    if (n_max > count) {
        free(primes);
        return ERROR_OVERFLOW;
    }
    *prime_out = primes;
    return OK;
}

void print_prime(const int *arr_idx, int len, const int *prime) {

    for (int i = 0; i < len; ++i) {
        int idx = arr_idx[i];
        printf("num by idx %d: %d\n", idx, prime[idx - 1]);
    }
}
