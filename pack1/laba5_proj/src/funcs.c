#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>

#include "../include/funcs.h"
#include "../include/return_codes.h"

void err_status(return_codes status) {
	switch (status) {
		case OK:
			printf("ok :)\n");
			return;
		case INVALID_INPUT:
			printf("error: invalid input\n");
			return;
		case ERROR_OVERFLOW:
			printf("error: overflow\n");
			return;
        case ERROR_NULL:
            printf("error: null\n");
            return;
        case ERROR_ALLOC:
            printf("error: alloc\n");
            return;
		case UNKNOWN_FLAG:
			printf("error: unknown flag\n");
			return;
	}
	return;
}

int is_flag(const char* flag) {
    if (strlen(flag) < 2 || strlen(flag) > 3) {
        return INVALID_INPUT;
    }
    if (flag[0] != '-' && flag[0] != '/') {
        return INVALID_INPUT;
    }
    char f;
	if (strlen(flag) == 3) {
		f = flag[2];
	} else {
		f = flag[1];
	}
    switch(f) {
        case 'd':
        case 'i':
        case 's':
        case 'a':
            return OK;
        default:
            return UNKNOWN_FLAG;
    }
}

int remove_arab(FILE *file_in, FILE *file_out) {
    if (!file_in || !file_out) {
        return ERROR_NULL;
    }
    int c;
    while ((c = fgetc(file_in)) != EOF) {
        if (!isdigit(c)) {
            if (fputc(c, file_out) == EOF) {
                return ERROR_OVERFLOW;
            }
        }
    }
    return OK;
}

int count_latin(FILE *file_in, FILE *file_out) {
    if (!file_in || !file_out) {
        return ERROR_NULL;
    }
    char str[4096];
    while (fgets(str, sizeof(str), file_in)) {
        int count = 0;
        for (int i = 0; str[i]; i++)
            if (isalpha((unsigned char)str[i]))
                count++;
        if (fprintf(file_out, "%d\n", count) < 0) {
            return ERROR_OVERFLOW;
        }
    }
    return OK;
}

int count_random(FILE *file_in, FILE *file_out) {
    if (!file_in || !file_out) {
        return ERROR_NULL;
    }
    char str[4096];
    while (fgets(str, sizeof(str), file_in)) {
        int count = 0;
        for (int i = 0; str[i]; i++)
            if (!(isalpha((unsigned char)str[i])) && !(isdigit((unsigned char)str[i])) && str[i] != ' ' && str[i] != '\n') {
                count++;
            }
        if (fprintf(file_out, "%d\n", count) < 0) {
            return ERROR_OVERFLOW;
        }
    }
    return OK;
}

int replace_to_ascii(FILE *file_in, FILE *file_out) {
    if (!file_in || !file_out) {
        return ERROR_NULL;
    }
    int c;
    while ((c = fgetc(file_in)) != EOF) {
        if (isdigit(c) || c == '\n') {
            if (fputc(c, file_out) == EOF) {
                return ERROR_OVERFLOW;
            }
        } else {
            if (fprintf(file_out, "%02X", (unsigned char)c) < 0) {
                return ERROR_OVERFLOW;
            }
        }
    }

    return OK;
}



double to_stepen(double x, int stepen) {
    double res = 1;
    if (stepen > 0) {
        for (int i = 0; i < stepen; ++i) {
            res *= x;
        }
    } else {
        for (int i = 0; i < abs(stepen); ++i) {
            res /= x;
        }
    }
    return res;
}
