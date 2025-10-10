#pragma once
#include "return_codes.h"

int str_to_int(const char *str, int *out);
int str_to_double(const char *str, double *out);
int is_flag(const char* flag);
void err_status(return_codes status);
void solution_status(solution_codes status);

void koeff(double eps, double x, double y, double z);
int solve_uravnenie(double eps, double a, double b, double c, double *res, double *res1, solution_codes *solut);
int have_seen(double eps, double seen[][3], int count, double a, double b, double c, int *is_seen);
void print_solution(enum solution_codes *solut, double a, double b, double c, double res, double res1);
int kratno(int x, int y, int *result);
int treugolnik(double eps, double a, double b, double c, int *result);
