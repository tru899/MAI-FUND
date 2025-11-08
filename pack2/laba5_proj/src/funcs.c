#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

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
		case INVALID_BASE:
			printf("error: invalid base\n");
			return;
		case ERROR_OVERFLOW:
			printf("error: overflow\n");
			return;
		case NO_MULTIPLES:
			printf("error: no multiplies\n");
			return;
		case ERROR_ALLOC:
			printf("error: alloc\n");
			return;
        case INVALID_PATH:
            printf("error: invalid path\n");
            return;
		case UNKNOWN_FLAG:
			printf("error: unknown flag\n");
			return;
	}
	return;
}

int open_files(const char *input_path, const char *output_path) {
    FILE *input = fopen(input_path, "r");
    if (!input) {
        return INVALID_PATH;
    }

    FILE *output = fopen(output_path, "w");
    if (!output) {
        fclose(input);
        return INVALID_PATH;
    }

    process_file(input, output);

    fclose(input);
    fclose(output);
    return OK;
}


int separate_word_eighty(char *dest, char *src) {
    int last_gap = -1;
    int i = 0;

    while (src[i] != '\0' && i < 80) {
        dest[i] = src[i];
        if (src[i] == ' ') {
            last_gap = i;
        }
        i++;
    }

    if (src[i] == '\0' || i < 80) {
        dest[i] = '\0';
        return i;
    }
    
    if (last_gap != -1) {
        dest[last_gap] = '\0';
        return last_gap + 1;
    } else {
        dest[80] = '\0';
        return 80;
    }
}

char* del_gaps(char* str) {
    while (*str == ' ') {
        str++;
    }
    return str;
}

int count_words(char* str) {
    int count = 0;
    int word_flag = 0;
    int len = strlen(str);
    for (int i = 0; i < len; ++i) {
        if (str[i] != ' ' && !word_flag) {
            word_flag = 1;
            count++;
        } else if (str[i] == ' ') {
            word_flag = 0;
        }
    }
    return count;
}

void add_line_to_eigthy(char* line, FILE* output) {
    int len = strlen(line);
    int words = count_words(line);
    char res[81];
    int res_i = 0;

    if (words <= 1 || len == 80) {
        fputs(line, output);
        fputc('\n', output);
        return;
    }
    
    int gaps = words - 1;
    int additive_gaps = (80 - len) / gaps;
    int beginnig_additive_gaps = (80 - len) % gaps;
    int i = 0;
    
    if (len < 80 && words > 1) {
        while (line[i] != '\0' && res_i < 80) {
            if (line[i] != ' ') {
                res[res_i++] = line[i++];
            } else {
                while (line[i] == ' ') {
                    i++;
                }
                if (gaps > 0) {
                    res[res_i++] = ' '; //first base gap
                    for (int k = 0; k < additive_gaps && res_i < 80; ++k) {
                        res[res_i++] = ' ';
                    }
                    if (beginnig_additive_gaps > 0 && res_i < 80) {
                        res[res_i++] = ' ';
                        beginnig_additive_gaps--;
                    }
                    gaps--;
                }
            }
        }
    }
    res[res_i] = '\0';
    fputs(res, output);
    fputc('\n', output);
}

void process_line(char* str, FILE* output) {
    while(*str != '\0') {
        str = del_gaps(str);
        if (*str == '\0' || *str == '\n') {
            break;
        }
        char new_str[81];
        int getter = separate_word_eighty(new_str, str);
        str += getter; //сместит усказатель на др слово

        int new_len = strlen(new_str);
        if (new_len < 80) {
            add_line_to_eigthy(new_str, output);
        } else {
            fputs(new_str, output);
            fputc('\n', output);
        }
    }
}

void process_file(FILE* input, FILE* output) {
    char str_buf[1024];
    while (fgets(str_buf, sizeof(str_buf), input)) {
        char* line = del_gaps(str_buf);
        size_t len_line = strlen(line);
        
        if (len_line > 0 && line[len_line - 1] == '\n') {
            line[len_line - 1] = '\0';
            len_line--;
        }

        if (len_line <= 80) {
            fputs(line, output);
            fputc('\n', output);
        } else {
            process_line(line, output);
        }
    }
}

int are_same_filepaths(const char *path1, const char *path2) {
    char canon_path1[PATH_MAX];
    char canon_path2[PATH_MAX];

    if (realpath(path1, canon_path1) == NULL) {
        return INVALID_PATH;
    }
    if (access(path2, F_OK) != 0) { //существует ли файл
        return INVALID_PATH;
    }
    if (realpath(path2, canon_path2) == NULL) {
        return INVALID_PATH;
    }
    return strcmp(canon_path1, canon_path2) == 0;
}
