#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#include <stdint.h>
#include "../include/funcs.h"
#include "../include/return_codes.h"


int main(int argc, char *argv[]) {
    if (argc != 2) {
        err_status(INVALID_INPUT);
        return INVALID_INPUT;
    }
    
    char *e = argv[1];
    double eps;
    return_codes status;

    status = str_to_double(e, &eps);
    if (status != OK) {
        err_status(status);
        return status;
    }

    if (eps <= 0) {
        err_status(INVALID_INPUT);
        return INVALID_INPUT;
    }
    print_integral(eps);
    return OK;
}
