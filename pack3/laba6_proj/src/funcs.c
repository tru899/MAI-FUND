#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/funcs.h"
#include "../include/return_codes.h"

void err_status(return_codes status) {
	switch (status) {
		case OK:
			printf("true bracket structure\n");
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
        case WRONG_BRACKETS:
            printf("wrong brackets struckture\n");
            return;
        case EMPTY_STACK:
            printf("error: stack is empty\n");
            return;
		case UNKNOWN_FLAG:
			printf("error: unknown flag\n");
			return;
	}
	return;
}

// () [] {} <>
//stack is needed

int check_brackets(const char *str) {
	if (!str) {
		return INVALID_INPUT;
	}

	Stack s;
	if (init_stack(&s) != OK) {
		return ERROR_ALLOC;
	}

	for (int i = 0; str[i] != '\0'; ++i) {
		char c = str[i];
		if (c == '(' || c == '[' || c == '{' || c == '<') {
			if (push_stack(&s, c) != OK) {
				free_stack(&s);
				return ERROR_ALLOC;
			}
		}

		if (c == ')' || c == ']' || c == '}' || c == '>') {
			if (s.size == 0) {
				free_stack(&s);
				return WRONG_BRACKETS;
			}
			char last_bracket;
			pop_stack(&s, &last_bracket);
			if ((c == ')' && last_bracket != '(') ||
				(c == ']' && last_bracket != '[') ||
				(c == '}' && last_bracket != '{') ||
				(c == '>' && last_bracket != '<')) {
					free_stack(&s);
					return WRONG_BRACKETS;
				}
		}
	}
	int res;
	if (s.size == 0) {
		res = OK;
	} else {
		res = WRONG_BRACKETS;
	}

	free_stack(&s);
	return res;
}

int init_stack(Stack *s) {
	s->size = 0;
	s->capacity = 8;
	s->data = (char*)malloc(s->capacity * sizeof(char));
	if (s->data == NULL) {
		return ERROR_ALLOC;
	}
	return OK;
}

int push_stack(Stack *s, char val) {
	if (s->size == s->capacity) {
		s->capacity *= 2;
		char *tmp = realloc(s->data, s->capacity * sizeof(char));
		if (tmp == NULL) {
			return ERROR_ALLOC;
		}
		s->data = tmp;
	}
	s->data[s->size] = val;
	s->size++;
	return OK;
}

int pop_stack(Stack *s, char *val) {
	if (s->size == 0) {
		return EMPTY_STACK;
	}

	*val = s->data[s->size - 1];
	s->size--;
	return OK;
}

void free_stack(Stack *s) {
	free(s->data);
	s->data = NULL;
	s->size = 0;
	s->capacity = 0;
}

