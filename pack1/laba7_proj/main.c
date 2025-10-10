#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "../include/funcs.h"
#include "../include/return_codes.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return INVALID_INPUT;
    }
    
    char buf[1024];
    FILE *file_in = fopen(argv[1], "r");
    FILE *file_out = fopen(argv[2], "w");

    if (file_in == NULL) {
        return ERROR_OPEN_FILE;
    }

    if (file_out == NULL) {
        fclose(file_in);
        return ERROR_OPEN_FILE;
    }
    
    return_codes status = OK;
    while (fgets(buf, sizeof(buf), file_in)) {
        int i = 0;
        while (buf[i] != '\0') {
            while (buf[i] != '\0' && is_space(buf[i]) == 1) {
                i++;
            }
            if (buf[i] == '\0') {
                break;
            }

            char token[256];
            int t = 0;
            while (buf[i] != '\0' && is_space(buf[i]) == 0 && t < 255) {
                token[t] = buf[i];
                t++;
                i++;
            }
            token[t] = '\0';

            const char *num = token;
            return_codes token_status = OK;
            int is_negative = 0;

            if (num[0] == '-') {
                is_negative = 1;
                num++;
                if (num[0] == '\0') {
                    token_status = INVALID_INPUT;
                }
            }

            while (num[0] == '0' && num[1] != '\0') {
                num++;
            }

            int base = get_base(num);

            if (base == INVALID_INPUT) {
                token_status = INVALID_INPUT;
            } else {
                if (base < 2 || base > 36) {
                    token_status = INVALID_BASE;
                }
            }

            if (token_status == OK) {
                long long decimal = to_dec(num, base);
                if (decimal == ERROR_OVERFLOW) {
                    token_status = ERROR_OVERFLOW;
                } else {
                    if (is_negative == 1) {
                        decimal = -decimal;
                    }
                    fprintf(file_out, "num: %s; base: %d; to_decimal: %lld\n", token, base, decimal);
                }
            }

            if (token_status != OK) {
                if (token_status == INVALID_INPUT) {
                    fprintf(file_out, "num: %s; error: invalid input\n", token);
                } else if (token_status == INVALID_BASE) {
                    fprintf(file_out, "num: %s; error: invalid base\n", token);
                } else if (token_status == ERROR_OVERFLOW) {
                    fprintf(file_out, "num: %s; error: overflow\n", token);
                }
                if (status == OK) {
                    status = token_status;
                }
            }
        }
    }
    fclose(file_in);
    fclose(file_out);
    return OK;
}
