#pragma once
#include "return_codes.h"

void err_status(return_codes status);
int is_flag(const char* flag);

int remove_arab(FILE *in, FILE *out);
int count_latin(FILE *in, FILE *out);
int count_random(FILE *in, FILE *out);
int replace_to_ascii(FILE *in, FILE *out);
