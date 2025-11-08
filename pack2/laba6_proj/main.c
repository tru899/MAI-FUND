#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/funcs.h"
#include "../include/return_codes.h"

void print_menu() {
    printf("choose action\n");
    printf("1. search by id\n");
    printf("2. search by name\n");
    printf("3. search by surname\n");
    printf("4. search by group\n");
    printf("5. sort by id\n");
    printf("6. sort by name\n");
    printf("7. sort by surname\n");
    printf("8. sort by group\n");
    printf("9. get students with avg marks greater than others\n");
    printf("0. exit\n");
}

int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        return INVALID_INPUT;
    }
    
    const char *input_path = argv[1];
    const char *output_path = NULL;

    Student *students = NULL;
    size_t count = 0;

    return_codes status;

    status = read_files(input_path, &students, &count);
    if (status != OK) {
        err_status(status);
        return status;
    }

    FILE *output = NULL;
    
    if (argc == 3) {
        output_path = argv[2];
        output = fopen(output_path, "w");
        if (!output) {
            return INVALID_PATH;
        }
        if (are_same_filepaths(input_path, output_path)) {
            printf("error: input and output files are the same\n");
            return INVALID_INPUT;
        }
    }

    int f;
    char buf[256];
    
    do {
        print_menu();
        if (fgets(buf, sizeof(buf), stdin) == NULL) {
            break;
        }
        if (sscanf(buf, "%d", &f) != 1) {
            f = -1;
        }
        switch (f) {
            case 1: {
                unsigned int id;
                printf("input id: ");
                if (fgets(buf, sizeof(buf), stdin) != NULL) {
                    if (sscanf(buf, "%u", &id) == 1) {
                        search_id(students, count, id, output);
                    } else {
                        printf("invalid format for id\n");
                    }
                }
                break;
            }
            case 2:
                printf("input name: ");
                if (fgets(buf, sizeof(buf), stdin) != NULL) {
                    buf[strcspn(buf, "\n")] = '\0';
                    search_name(students, count, buf);
                }
                break;
            case 3:
                printf("input surname: ");
                if (fgets(buf, sizeof(buf), stdin) != NULL) {
                    buf[strcspn(buf, "\n")] = '\0';
                    search_surname(students, count, buf);
                }
                break;
            case 4:
                printf("input group: ");
                if (fgets(buf, sizeof(buf), stdin) != NULL) {
                    buf[strcspn(buf, "\n")] = '\0';
                    search_group(students, count, buf);
                }
                break;
            case 5:
                sort_id(students, count);
                break;
            case 6:
                sort_name(students, count);
                break;
            case 7:
                sort_surname(students, count);
                break;
            case 8:
                sort_group(students, count);
                break;
            case 9:
                print_great_avg_students(students, count, output);
                break;
            case 0:
                break;
            default:
                err_status(UNKNOWN_FLAG);
                continue;
        }
    } while (f != 0);
    free_students_array(students, count);
    if (output != NULL) {
        fclose(output);
    }

    return OK;
}
