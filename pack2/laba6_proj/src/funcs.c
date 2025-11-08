#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
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

void free_student_fields(Student *s) {
    if (s) {
        free(s->name);
        free(s->surname);
        free(s->group);
        free(s->marks);
    }
}

void free_students_array(Student *students, size_t count) {
    if (!students) return;
    for (size_t i = 0; i < count; ++i) {
        free_student_fields(&students[i]);
    }
    free(students);
}

int str_is_alpha(const char *str) {
    if (str[0] == '\0') {
        return 0;
    }

    for (int i = 0; str[i] != '\0'; ++i) {
        if (!isalpha(str[i])) {
            return 0;
        }
    }
    return 1;
}

return_codes read_files(const char *input_path, Student **arr_out, size_t *count_out) {
	FILE *input = fopen(input_path, "r");
	if (!input) {
		return INVALID_PATH;
	}

	size_t size = 0;
	size_t capacity = 8;
	Student *students = (Student*)malloc(capacity * sizeof(Student));

	if (students == NULL) {
		fclose(input);
		return ERROR_ALLOC;
	}
	
	unsigned int id = 0;
	char name_buf[256];
	char surname_buf[256];
	char group_buf[256];
	unsigned int marks[5];

	while (fscanf(input, "%u %255s %255s %255s %u %u %u %u %u", &id, name_buf, surname_buf, group_buf, &marks[0], &marks[1], &marks[2], &marks[3], &marks[4]) == 9) {
		if (str_is_alpha(name_buf) == 0 || str_is_alpha(surname_buf) == 0) {
			printf("invalid format for name or surname\n");
			continue;
		}

		if (size == capacity) {
			capacity *= 2;
			Student *tmp = realloc(students, capacity * sizeof(Student));
			if (tmp == NULL) {
				free_students_array(students, size);
				fclose(input);
				return ERROR_ALLOC;
			}
			students = tmp;
		}
		
		students[size].name = NULL;
		students[size].surname = NULL;
		students[size].group = NULL;
		students[size].marks = NULL;
		
		size_t name_len = strlen(name_buf);
		students[size].name = (char*)malloc((name_len + 1) * sizeof(char));

		size_t surname_len = strlen(surname_buf);
		students[size].surname = (char*)malloc((surname_len + 1) * sizeof(char));
		
		size_t group_len = strlen(group_buf);
		students[size].group = (char*)malloc((group_len + 1) * sizeof(char));
		
		students[size].marks = (unsigned char*)malloc(5 * sizeof(unsigned char));

		if (!students[size].name || !students[size].surname || !students[size].group || !students[size].marks) {
			free_students_array(students, size + 1);
			fclose(input);
			return ERROR_ALLOC;
		}

		strcpy(students[size].name, name_buf);
		strcpy(students[size].surname, surname_buf);
		strcpy(students[size].group, group_buf);

		students[size].id = id;
		for (int i = 0; i < 5; ++i) {
			students[size].marks[i] = (unsigned char)marks[i];
		}
		size++;
	}

	fclose(input);
	
	*arr_out = students;
	*count_out = size;
	return OK;
}

void print_great_avg_students(Student *students, size_t count, FILE *output) {
	int found = 0;
	double all_marks = get_all_avg(students, count);
	double greater_marks = 0;
	for (int i = 0; i < count; ++i) {
		greater_marks = get_avg_marks(&students[i]);
		if (greater_marks > all_marks) {
			found = 1;
			if (output) {
				fprintf(output, "student name: %s, surname: %s, avg marks: %.2f\n", students[i].name, 
					students[i].surname, greater_marks);
			} else {
				printf("student name: %s, surname: %s, avg marks: %.2f\n", students[i].name, 
					students[i].surname, greater_marks);
			}
		}
	}
	if (!found) {
		if (output) {
			fprintf(output, "there's no student with marks greater than %.2f\n", all_marks);
		} else {
			printf("there's no student with marks greater than %.2f\n", all_marks);
		}
	}
}

void search_id(Student *students, size_t count, unsigned int id, FILE *output) {
	int found = 0;
	for (int i = 0; i < count; ++i) {
		if (students[i].id == id) {
			found = 1;
			double avg_mark = get_avg_marks(&students[i]);
			if (output) {
				fprintf(output, "student id: %u, name: %s, surname: %s, group: %s, avg marks: %.2f\n", students[i].id , students[i].name, 
					students[i].surname, students[i].group, avg_mark);
			} else {
				printf("student id: %u, name: %s, surname: %s, group: %s, avg marks: %.2f\n", students[i].id , students[i].name, 
					students[i].surname, students[i].group, avg_mark);
			}
		}
	}
	if (!found) {
		if (output) {
			fprintf(output, "there's no student with %u id\n", id);
		} else {
			printf("there's no student with %u id\n", id);
		}
	}
}

void search_name(Student *students, size_t count, const char *name) {
	int found = 0;
	if (str_is_alpha(name) == 0) {
		printf("invalid format for name\n");
		return ;
	}

	for (int i = 0; i < count; ++i) {
		if (strcmp(students[i].name, name) == 0) {
			found = 1;
			printf("student with name %s was found\n", students[i].name);
		}
	}
	if (!found) {
		printf("student with name %s was NOT found\n", name);
	}
}

void search_surname(Student *students, size_t count, const char *surname) {
	int found = 0;
	if (str_is_alpha(surname) == 0) {
		printf("invalid format for surname\n");
		return ;
	}

	for (int i = 0; i < count; ++i) {
		if (strcmp(students[i].surname, surname) == 0) {
			found = 1;
			printf("student with surname %s was found\n", students[i].surname);
		}
	}
	if (!found) {
		printf("student with surname %s was NOT found\n", surname);
	}
}

void search_group(Student *students, size_t count, const char *group) {
	int found = 0;	
	for (int i = 0; i < count; ++i) {
		if (strcmp(students[i].group, group) == 0) {
			found = 1;
			printf("student with group %s was found\n", students[i].group);
		}
	}
	if (!found) {
		printf("student with group %s was NOT found\n", group);
	}
}

double get_avg_marks(const Student *students) {
	double total_avg = 0;
	for (int i = 0; i < 5; ++i) {
		total_avg += students->marks[i];
	}
	total_avg /= 5.0;
	return total_avg;
}

double get_all_avg(const Student *students, size_t count) {
	double all_avg = 0;
	double total = 0;
	
	if (count == 0) {
		return 0.0;
	}

	for (size_t i = 0; i < count; ++i) {
		all_avg += get_avg_marks(&students[i]);
	}
	total = all_avg / count;
	return total;
}

int cmp_id(const void *student_a, const void *student_b) {
	const Student *s1 = (const Student*)student_a;
	const Student *s2 = (const Student*)student_b;
	if (s1->id > s2->id) {
		return 1;
	} else if (s1->id < s2->id) {
		return -1;
	}
	return 0;
}

int cmp_name(const void *student_a, const void *student_b) {
	const Student *s1 = (const Student*)student_a;
	const Student *s2 = (const Student*)student_b;
	return strcmp(s1->name, s2->name);	
}

int cmp_surname(const void *student_a, const void *student_b) {
	const Student *s1 = (const Student*)student_a;
	const Student *s2 = (const Student*)student_b;
	return strcmp(s1->surname, s2->surname);
}

int cmp_group(const void *student_a, const void *student_b) {
	const Student *s1 = (const Student*)student_a;
	const Student *s2 = (const Student*)student_b;
	return strcmp(s1->group, s2->group);
}

void print_all_students(Student *students, size_t count) {
    if (count == 0) {
        printf("there're no students\n");
        return;
    }
    for (int i = 0; i < count; ++i) {
        printf("student id: %u, name: %s, surname: %s, group: %s\n",
               students[i].id, students[i].name, students[i].surname, students[i].group);
    }
}

void sort_id(Student *students, size_t count) {
	qsort(students, count, sizeof(Student), cmp_id);
	printf("sorted by id\n");
	print_all_students(students, count);
}

void sort_name(Student *students, size_t count) {
	qsort(students, count, sizeof(Student), cmp_name);
	printf("sorted by name\n");
	print_all_students(students, count);
}

void sort_surname(Student *students, size_t count) {
	qsort(students, count, sizeof(Student), cmp_surname);
	printf("sorted by surname\n");
	print_all_students(students, count);
}

void sort_group(Student *students, size_t count) {
	qsort(students, count, sizeof(Student), cmp_group);
	printf("sorted by group\n");
	print_all_students(students, count);
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
