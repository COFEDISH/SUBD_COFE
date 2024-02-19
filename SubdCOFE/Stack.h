#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int elem_stack[MAX_SIZE];
    int top_stack;
} Stack;

void initialize_stack(Stack* stack);
bool is_empty_stack(Stack* stack);
bool is_full_stack(Stack* stack);
void push_stack(Stack* stack, int value);
int pop_stack(Stack* stack, const char* file_name, const char* table_name);
int pop_stack_save(Stack* stack);
int top_stack(Stack* stack);
void print_stack(Stack* stack);
#endif /* STACK_H */

