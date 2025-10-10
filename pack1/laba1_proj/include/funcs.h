#pragma once
#include "return_codes.h"

int str_to_int(const char *str, int *out);
int is_flag(const char* flag);
void err_status(return_codes status);

int is_natural(int x, int *found_nat, int *multiples, int *count);
int is_prime(int x, int *prime_flag);
int to_hex(int x, char *buf);
int power_table(int x, long long table[10][10]);
int sum_natural(int x, unsigned long long *result);
int factorial(int x, long long *result);

void print_natural(int x, int *multiples, int count);
void print_table(int x, long long table[10][10]);