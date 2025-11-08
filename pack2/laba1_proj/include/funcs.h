#pragma once
#include "return_codes.h"

void err_status(return_codes status);
long long gcd(long long a, long long b);
void shortenFrac(long long *chisl, long long *znam);
return_codes getPrimeMultipliers(long long num, int *total_count, long long **res_out);
return_codes isFinite(double frac, long long *base_mults, int base_mults_count, bool *result_out);
return_codes checkFiniteFracs(int base, int count, ...);
