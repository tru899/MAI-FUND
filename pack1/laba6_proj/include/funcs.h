#pragma once
#include "return_codes.h"

int str_to_double(const char *str, double *out);
void err_status(return_codes status);

double f1(double x);
double f2(double x);
double f3(double x);
double f4(double x);

double integrals (double eps, double (*f)(double));
void print_integral(double eps);
