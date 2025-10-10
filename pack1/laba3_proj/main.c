#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../include/funcs.h"
#include "../include/return_codes.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        err_status(INVALID_INPUT);
        return INVALID_INPUT;
    }

    char *flag = argv[1];
    return_codes status;

    status = is_flag(flag);
    if (status != OK) {
        err_status(status);
        return status;
    }

    double eps, a, b, c, res, res1;
    int x, y, result;
    char f = flag[1];
    switch(f) {
        case 'q':
            if (argc != 6) {
                err_status(INVALID_INPUT);
                return INVALID_INPUT;
            }

            str_to_double(argv[2], &eps);
            str_to_double(argv[3], &a);
            str_to_double(argv[4], &b);
            str_to_double(argv[5], &c);

            status = str_to_double(argv[2], &eps);
            if (status != OK) {
                err_status(status);
                return status;
            }
            status = str_to_double(argv[3], &a);
            if (status != OK) {
                err_status(status);
                return status;
            }
            status = str_to_double(argv[4], &b);
            if (status != OK) {
                err_status(status);
                return status;
            }
            status = str_to_double(argv[5], &c);
            if (status != OK) {
                err_status(status);
                return status;
            }
            
            koeff(eps, a, b, c);
            return OK;
        case 'm':
            if (argc != 4) {
                err_status(INVALID_INPUT);
                return INVALID_INPUT;
            }

            str_to_int(argv[2], &x);
            str_to_int(argv[3], &y);

            status = str_to_int(argv[2], &x);
            if (status != OK) {
                err_status(status);
                return status;
            }
            status = str_to_int(argv[3], &y);
            if (status != OK) {
                err_status(status);
                return status;
            }

            status = kratno(x, y, &result);
            if (status != OK) {
                err_status(status);
                return status;
            }
            printf("%d is kratno %d\n", x ,y);
            return OK;
        case 't':
            if (argc != 6) {
                err_status(INVALID_INPUT);
                return INVALID_INPUT;
            }

            str_to_double(argv[2], &eps);
            str_to_double(argv[3], &a);
            str_to_double(argv[4], &b);
            str_to_double(argv[5], &c);

            status = str_to_double(argv[2], &eps);
            if (status != OK) {
                err_status(status);
                return status;
            }
            status = str_to_double(argv[3], &a);
            if (status != OK) {
                err_status(status);
                return status;
            }
            status = str_to_double(argv[4], &b);
            if (status != OK) {
                err_status(status);
                return status;
            }
            status = str_to_double(argv[5], &c);
            if (status != OK) {
                err_status(status);
                return status;
            }

            status = treugolnik(eps, a, b, c, &result);
            if (status != OK) {
                err_status(status);
                return status;
            }
            if (!result) {
                printf("%.3f, %.3f, %.3f are NOT sides of rectangle treugolnik\n", a, b, c);
                return OK;
            } else {
                printf("%.3f, %.3f, %.3f are sides of rectangle treugolnik\n", a, b, c);
                return OK;
            }
            return OK;
        default:
            err_status(UNKNOWN_FLAG);
            return UNKNOWN_FLAG;
    }

    return OK;
}