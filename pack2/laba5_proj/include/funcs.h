#pragma once
#include "return_codes.h"

void err_status(return_codes status);

int open_files(const char *input_path, const char *output_path);
int separate_word_eighty(char *dest, char *src);
char* del_gaps(char* str);
int count_words(char* str);
void add_line_to_eigthy(char* line, FILE* output);
void process_line(char* str, FILE* output);
void process_file(FILE* input, FILE* output);
int are_same_filepaths(const char *path1, const char *path2);
