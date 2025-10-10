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
    
    char *T = argv[1];
    int t_int;

    return_codes status;

    status = str_to_int(T, &t_int);
    if (status != OK) {
        err_status(INVALID_INPUT);
        return INVALID_INPUT;
    }

    if (t_int <= 0) {
        err_status(INVALID_INPUT);
        return INVALID_INPUT;
    }

    int *arr_idx = NULL;
    status = vvod(t_int, &arr_idx);
    if (status != OK) {
        err_status(status);
        return status;
    }
    
    int n_max = find_max_n(arr_idx, t_int);

    int *prime = NULL;
    status = is_prime(n_max, &prime);  
    if (status != OK) {
        free(arr_idx);
        err_status(status);
        return status;
    }
    print_prime(arr_idx, t_int, prime);

    free(arr_idx);
    free(prime);

    if (status != OK) {
        err_status(status);
        return status;
    }

    return OK;
}
