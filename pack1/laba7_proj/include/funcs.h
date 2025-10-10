#pragma once
#include "return_codes.h"

void err_status(return_codes status);
int get_base(const char* num_str);
long long to_dec(const char* num_str, int base);
int is_space(char str);
