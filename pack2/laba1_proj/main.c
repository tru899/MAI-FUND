#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdbool.h>
#include <math.h>
#include <limits.h>
#include "../include/funcs.h"
#include "../include/return_codes.h"

int main() {
    return_codes status;

    printf("\n");
    printf("first: base 2\n");
    status = checkFiniteFracs(2, 3, 0.005, 0.75, 0.1);
    if (status != OK) {
        err_status(status);
        return status;
    }

    printf("\n");
    printf("second: base 3\n");
    status = checkFiniteFracs(3, 2, 1.0/3.0, 0.2);
     if (status != OK) {
        err_status(status);
    }

    printf("\n");
    printf("third: base 10\n");
    status = checkFiniteFracs(10, 3, 0.125, 0.33333333333333, 1.0/3.0);
    if (status != OK) {
        err_status(status);
        return status;
    }

    printf("\n");
    printf("fourth: base 12\n");
    status = checkFiniteFracs(12, 2, 1.0/3.0, 0.2);
     if (status != OK) {
        err_status(status);
    }

    printf("\n");
    printf("fifth: error\n");
    status = checkFiniteFracs(1, 1, 0.001);
    if (status != OK) {
        err_status(status);
    }

    printf("\n");
    printf("sixth: wrong interval\n");
    status = checkFiniteFracs(18, 4, 1.5, 0.0, 1.0/0.0, -1.1);
    if (status != OK) {
        err_status(status);
    }

    return OK;
}
