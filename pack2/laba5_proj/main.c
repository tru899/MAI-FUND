#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/funcs.h"
#include "../include/return_codes.h"

int main() {
    char input_path[1024];
    char output_path[1024];

    printf("enter input path: ");
    // scanf("%s", input_path);
    if (fgets(input_path, sizeof(input_path), stdin) == NULL) {
        return INVALID_PATH;
    }

    printf("enter output path: ");
    // scanf("%s", output_path);
    if (fgets(output_path, sizeof(output_path), stdin) == NULL) {
        return INVALID_PATH;
    }

    input_path[strcspn(input_path, "\n")] = '\0';
    output_path[strcspn(output_path, "\n")] = '\0';

    if (are_same_filepaths(input_path, output_path)) {
        printf("error: input and output files are the same\n");
        return INVALID_INPUT;
    }

    return_codes status;
    status = open_files(input_path, output_path); 
    if (status != OK) {
        err_status(status);
        return status;
    }
    return OK;
}
