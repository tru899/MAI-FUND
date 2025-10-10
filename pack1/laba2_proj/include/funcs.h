#pragma once
#include "return_codes.h"

int str_to_int(const char *str, int *out);
void err_status(return_codes status);

int vvod(int count, int **arr_out);
int find_max_n(const int *arr, int len);
int is_prime(int max_n, int **prime_out);
void print_prime(const int *arr_idx, int len, const int *prime);
