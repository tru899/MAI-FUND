#pragma once
#include "return_codes.h"

typedef struct {
    unsigned int id;
    char *name;
    char *surname;
    char *group;
    unsigned char *marks;
} Student;

void err_status(return_codes status);
void free_student_fields(Student *s);
void free_students_array(Student *students, size_t count);
int str_is_alpha(const char *str);
void print_all_students(Student *students, size_t count);
int are_same_filepaths(const char *path1, const char *path2);

return_codes read_files(const char *input_path, Student **arr_out, size_t *count_out);
void print_great_avg_students(Student *students, size_t count, FILE *output);
void search_id(Student *students, size_t count, unsigned int id, FILE *output);
void search_name(Student *students, size_t count, const char *name);
void search_surname(Student *students, size_t count, const char *surname);
void search_group(Student *students, size_t count, const char *group);

double get_avg_marks(const Student *students);
double get_all_avg(const Student *students, size_t count);

int cmp_id(const void *student_a, const void *student_b);
int cmp_name(const void *student_a, const void *student_b);
int cmp_surname(const void *student_a, const void *student_b);
int cmp_group(const void *student_a, const void *student_b);

void sort_id(Student *students, size_t count);
void sort_name(Student *students, size_t count);
void sort_surname(Student *students, size_t count);
void sort_group(Student *students, size_t count);
