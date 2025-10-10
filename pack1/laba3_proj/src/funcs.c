#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <float.h>
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

int is_flag(const char* flag) {
    if (strlen(flag) != 2) {
        return INVALID_INPUT;
    }
    if (flag[0] != '-' && flag[0] != '/') {
        return INVALID_INPUT;
    }
    char f = flag[1];
    switch(f) {
        case 'q':
        case 'm':
        case 't':
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

void solution_status(solution_codes status) {
    switch(status) {
        case NO_SOLUTIONS:
            printf("no solutions\n");
            return;
        case ONE_SOLUTION:
            printf("one solution\n");
            return;
        case TWO_SOLUTIONS:
            printf("two solutions\n");
            return;
        case INFINITE_SOLUTIONS:
            printf("infinite solutions\n");
            return;
    }
    return;
}

void koeff(double eps, double x, double y, double z) {
    double kf[3] = {x, y, z};
    int comb[6][3] = {
        {0, 1, 2},
        {0, 2, 1},
        {1, 0, 2},
        {1, 2, 0},
        {2, 0, 1},
        {2, 1, 0}
    };

    double seen[6][3];
    int seen_count = 0;
    int is_seen;

    for (int n = 0; n < 6; n++) {
        int i = comb[n][0];
        int j = comb[n][1];
        int k = comb[n][2];

        double a = kf[i];
        double b = kf[j];
        double c = kf[k];

        int status = have_seen(eps, seen, seen_count, a, b, c, &is_seen);
        if (status == OK && !is_seen) {
            double res=0, res1=0;
            solution_codes solut;
            status = solve_uravnenie(eps, a, b, c, &res, &res1, &solut);
            if (status == OK) {
                print_solution(&solut, a, b, c, res, res1);
                seen[seen_count][0] = a;
                seen[seen_count][1] = b;
                seen[seen_count][2] = c;
                seen_count++;
            }
        }
    }
}

int solve_uravnenie(double eps, double a, double b, double c, double *res, double *res1, solution_codes *solut) {
    double diskr = (b * b - (4 * a * c));

    if (fabs(a) < eps) {
        if (fabs(b) < eps) {
            if (fabs(c) < eps) {
                *solut = INFINITE_SOLUTIONS;
            } else {
                *solut =  NO_SOLUTIONS;
            }
        } else {
            *res = -c / b;
            *solut = ONE_SOLUTION;
        }
        return OK;
    }

    if (fabs(diskr) <= eps) {
        *res = -b / (a * 2);
        *solut = ONE_SOLUTION;
    } else if (diskr > 0) {
        *res = (-b + sqrt(diskr)) / (a * 2);
        *res1 = (-b - sqrt(diskr)) / (a * 2);
        *solut = TWO_SOLUTIONS;
    } else {
        *solut = NO_SOLUTIONS;
    }

    return OK;
}

int have_seen(double eps, double seen[][3], int count, double a, double b, double c, int *is_seen) {
    *is_seen = 0;
    for (int i = 0; i < count; i++) {
        if (fabs(seen[i][0] - a) < eps && fabs(seen[i][1] - b) < eps && fabs(seen[i][2] - c) < eps) {
            *is_seen = 1;
            break;
        }
    }
    return OK;
}

void print_solution(enum solution_codes *solut, double a, double b, double c, double res, double res1) {
    printf("a=%.3f, b=%.3f, c=%.3f => ", a, b, c);
    switch (*solut) {
        case NO_SOLUTIONS:
            printf("no soluttions\n");
            break;
        case ONE_SOLUTION:
            printf("x=%.3f\n", res);
            break;
        case TWO_SOLUTIONS:
            printf("x1=%.3f, x2=%.3f\n", res, res1);
            break;
        case INFINITE_SOLUTIONS:
            printf("infinite solutions\n");
            break;
    }
}

int kratno(int x, int y, int *result) {
    if (x == 0 || y == 0) {
        return INVALID_INPUT;
    }
    int is_kratno_flag = 0;
    if (x % y == 0) {
        is_kratno_flag = 1;
        return OK;
    } else {
        return NO_MULTIPLES;
    }

    *result = is_kratno_flag;
    return OK;
}

int treugolnik(double eps, double a, double b, double c, int *result) {
    if (a <= 0 || b <= 0 || c <= 0 || eps <= 0) {
        return INVALID_INPUT;
    }

    double sides[3] = {a, b, c};
    int side_idx_count = 0;
    double a_new, b_new;

    int max_idx = 0;

    for (int i = 1; i < 3; i++) {
        if (sides[i] > sides[max_idx]) {
            max_idx = i;
        }
    }

    for (int i = 0; i < 3; i++) {
        if (i != max_idx) {
            if (side_idx_count == 0) {
                a_new = sides[i];
            } else {
                b_new = sides[i];
            }
            side_idx_count++;
        }
    }
    double max_side = sides[max_idx];

    if (fabs(max_side * max_side - (a_new * a_new + b_new * b_new)) < eps) {
        *result = 1;
        return OK;
    } else {
        *result = 0;
        return OK;
    }

    return OK;
}
