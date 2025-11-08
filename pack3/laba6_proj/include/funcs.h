#pragma once
#include "return_codes.h"

// typedef struct Node {
//     char data;
//     struct Node* next;
//     struct Node* prev;
// } Node;

typedef struct {
    char *data;
    size_t size;
    size_t capacity;
} Stack;

void err_status(return_codes status);

int check_brackets(const char *str);
int init_stack(Stack *s);
int push_stack(Stack *s, char val);
int pop_stack(Stack *s, char *val);
void free_stack(Stack *s);
