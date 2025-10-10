#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>
#include "../include/funcs.h"
#include "../include/return_codes.h"

int str_to_double(const char *str, double *out) {
    char *endptr;
    double val = strtod(str, &endptr);

    if (val == HUGE_VAL || val == -HUGE_VAL) {
        return ERROR_OVERFLOW;
    }

    if (endptr == str || *endptr != '\0') {
        return INVALID_INPUT;
    }

    *out = val;
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

double f1(double x) { 
	if (x == 0) {
		return 1.0;
	} else {
		return log(1 + x) / x;
	}
}
double f2(double x) {
	return exp(-(x*x) / 2.0);
}
double f3(double x) {
	if (x >= 1) {
		x = 0.999999999;
	}
	return log(1 / (1 - x));
}
double f4(double x) {
	if (x == 0) {
		return 1.0; // 0/0 = 1
	} else {
		return pow(x, x);
	}
}

double integrals(double eps, double (*f)(double)) {
    double a = 0.0;
    double b = 1.0;
    int n = 5;
    double Iprev = 0.0;
    double I = 0.0;
	
    while (1) {
        double h = (b - a) / n;
        double sum = 0.0;

        for (int i = 1; i < n; i++) {
            double x = a + i * h; //коорд точки
            sum += f(x);	//значение функ в этих точках
        }

		I = ((f(a) + f(b)) / 2.0 + sum) * h;

        if (fabs(I - Iprev) < eps) {
            break;
        }
        Iprev = I;
        n *= 2;
    }
    return I;
}

void print_integral(double eps) {
	printf("res: %.7f\n", integrals(eps, f1));
	printf("res: %.7f\n", integrals(eps, f2));
	printf("res: %.7f\n", integrals(eps, f3));
	printf("res: %.7f\n", integrals(eps, f4));
}
