#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include <stdint.h>

#include "../include/funcs.h"
#include "../include/return_codes.h"

int main(int argc, char* argv[]) {
    if (argc < 3 || argc > 4) {
        return INVALID_INPUT;
    }

    const char *flag = argv[1];
    const char *file_in_path = argv[2];
    char file_out_path[512];

    int n_flag = (flag[0] == '-' || flag[0] == '/') && flag[1] == 'n';

    if (n_flag) {
        if (argc != 4) {
            return INVALID_INPUT;
        }
        strcpy(file_out_path, argv[3]);
    } else {
        strcpy(file_out_path, "out_");
        strcat(file_out_path, file_in_path);
    }

    FILE *file_in = fopen(file_in_path, "r");
    if (!file_in) {
        return ERROR_NULL;
    }

    FILE *file_out = fopen(file_out_path, "w");
    if (!file_out) {
        return ERROR_NULL;
    }
    return_codes status;

    status = is_flag(flag);
    if (status != OK) {
        err_status(status);
        fclose(file_in);
        fclose(file_out);
        return status;
    }

    char f;
    if (n_flag) {
        f = flag[2];
    } else {
        f = flag[1];
    }
    
    switch(f) {
        case 'd':
            status = remove_arab(file_in, file_out);
            break;
        case 'i':
            status = count_latin(file_in, file_out);
            break;
        case 's':
            status = count_random(file_in, file_out);
            break;
        case 'a':
            status = replace_to_ascii(file_in, file_out);
            break;
        default:
            status = UNKNOWN_FLAG;
            break;
    }
    fclose(file_in);
    fclose(file_out);
    return status;
}
