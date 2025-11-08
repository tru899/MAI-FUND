#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>
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
		case INVALID_BASE:
			printf("error: invalid base\n");
			return;
		case ERROR_OVERFLOW:
			printf("error: overflow\n");
			return;
		case NO_MULTIPLES:
			printf("error: no multiplies\n");
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

long long gcd(long long a, long long b) {
    long long tmp_swap;
    if (llabs(a) > llabs(b)) {
        tmp_swap = a;
        a = b;
        b = tmp_swap;
    }

    long long tmp;
    while (b != 0) {
        tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}

void shortenFrac(long long *chisl, long long *znam) {
    long long new_frac;
    new_frac = gcd(*chisl, *znam);
    *chisl /= new_frac;
    *znam /= new_frac;
}

return_codes getPrimeMultipliers(long long num, int *total_count, long long **res_out) {
    int size = 0;
    int capacity = 8;
    long long *res = (long long*)malloc(capacity * sizeof(long long));
    if (res == NULL) {
        return ERROR_ALLOC;
    }

    long long d = 2;
    while (d * d <= num) {
        if (num % d == 0) {
            bool is_unique = true;
            for (int i = 0; i < size; ++i) {
                if (res[i] == d) {
                    is_unique = false;
                    break;
                }
            }
            if (is_unique) {
                if (size == capacity) {
                    capacity *= 2;
                    long long *tmp = realloc(res, capacity * sizeof(long long));
                    if (tmp == NULL) {
                        free(res);
                        return ERROR_ALLOC;
                    }
                    res = tmp;
                }
                res[size++] = d;
            }
            while (num % d == 0) {
                num /= d;
            }
        }
        d++;
    }

    if (num > 1) {
        bool is_unique = true;
        for (int i = 0; i < size; ++i) {
            if (res[i] == num) {
                is_unique = false;
                break;
            }
        }
        if (is_unique) {
            if (size == capacity) {
                capacity *= 2;
                long long *tmp = realloc(res, capacity * sizeof(long long));
                if (tmp == NULL) {
                    free(res);
                    return ERROR_ALLOC;
                }
                res = tmp;
            }
            res[size++] = num;
        }
    }

    *total_count = size;
    *res_out = res;
    return OK;
}

return_codes isFinite(double frac, long long *base_mults, int base_mults_count, bool *result_out) {
    /*  metod no interrupt fracs
            x = a0 + 1 / (a1 + 1 / (a2 + 1 / ...)) */
    //  a0 = floor(x)
    //  Pn = AnPn-1 + Pn-2 -> P-1 = 1; Q-1 = 0; P0 = A0; Q0 = 1

    long long p0 = 0;
    long long q0 = 1;
    long long p1 = 1;
    long long q1 = 0;
    long long chisl, znam; //pn, qn
    double x = frac;

    int max_i = 1000;
    double eps = 1e-12;

    while (max_i--) {
        long long a = (long long)floor(x);
        chisl = a * p1 + p0;
        znam = a * q1 + q0;
        if (fabs(frac - (double)(chisl / znam)) < eps) {
            break;
        }

        p0 = p1;
        p1 = chisl;
        q0 = q1;
        q1 = znam;

        double r = x - a; //ostatok
        if (r < eps) {
            break;
        }
        x = 1.0 / r;
    }
    shortenFrac(&chisl, &znam);

    int count_znam_mults;
    long long *znam_mults = NULL;
    return_codes status = getPrimeMultipliers(znam, &count_znam_mults, &znam_mults);
    if (status != OK) {
        return status;
    }

    bool is_finite = true;
    for (int i = 0; i < count_znam_mults; ++i) {
        bool is_found = false;
        for (int j = 0; j < base_mults_count; ++j) {
            if (znam_mults[i] == base_mults[j]) {
                is_found = true;
                break;
            }
        }
        if (!is_found) {
            is_finite = false;
            break;
        }
    }
    
    free(znam_mults);
    *result_out = is_finite;
    return OK;
}

return_codes checkFiniteFracs(int base, int count, ...) {
    if (base < 2 || base > 36) {
        return INVALID_BASE;
    }
    if (count <= 0) {
        return INVALID_INPUT;
    }

    int base_mults_count;
    long long *base_mults = NULL;
    return_codes status = getPrimeMultipliers(base, &base_mults_count, &base_mults);
    if (status != OK) {
        return status;
    }
    
    va_list args;
    va_start(args, count);
    
    for (int i = 0; i < count; ++i) {
        double frac = va_arg(args, double);
        if (frac <= 0 || frac >= 1) {
            printf("%f is not in interval (0; 1)\n", frac);
            continue;
        }
        bool result;
        return_codes status = isFinite(frac, base_mults, base_mults_count, &result);
        if (status != OK) {
            free(base_mults);
            va_end(args);
            return status;
        }
        
        if (result == true) {
            printf("%f - fraction is finite\n", frac);
        } else {
            printf("%f - fraction is NOT finite\n", frac);
        }
    }

    free(base_mults);
    va_end(args);
    return OK;
}
