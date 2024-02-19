#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Stack.h"
#include "Save_and_Output.h"
#define MAX_SIZE 100

// Инициализация стека
void initialize_stack(Stack* stack) {
    stack->top_stack = -1; // Устанавливаем вершину стека в -1, что указывает на пустой стек
}

// Проверка на пустоту стека
bool is_empty_stack(Stack* stack) {
    return stack->top_stack == -1; // Возвращает true, если стек пуст, иначе false
}

// Проверка на переполнение стека
bool is_full_stack(Stack* stack) {
    return stack->top_stack == MAX_SIZE - 1; // Возвращает true, если стек переполнен, иначе false
}

// Помещение элемента на вершину стека
void push_stack(Stack* stack, int value) {
    if (is_full_stack(stack)) {
        printf("Стек переполнен\n"); // Выводим сообщение, если стек переполнен
    }
    else {
        stack->top_stack++;
        stack->elem_stack[stack->top_stack] = value; // Помещаем элемент на вершину стека
    }
}

// Извлечение элемента с вершины стека
int pop_stack(Stack* stack, const char* file_name, const char* table_name) {
    if (is_empty_stack(stack)) {
        printf("Стек пуст\n"); // Выводим сообщение, если стек пуст
        return -1;
    }
    else {
        int value = stack->elem_stack[stack->top_stack];
        stack->top_stack--;
        save_stack_to_file(stack, file_name, table_name); // Сохраняем стек в файл после извлечения элемента
        return value;
    }
}

// Извлечение элемента с вершины стека без сохранения
int pop_stack_save(Stack* stack) {
    if (is_empty_stack(stack)) {
        printf("Стек пуст\n"); // Выводим сообщение, если стек пуст
        return -1;
    }
    else {
        int value = stack->elem_stack[stack->top_stack];
        stack->top_stack--;
        return value;
    }
}

// Получение элемента с вершины стека без его удаления
int top_stack(Stack* stack) {
    if (is_empty_stack(stack)) {
        printf("Стек пуст\n"); // Выводим сообщение, если стек пуст
        return -1;
    }
    else {
        return stack->elem_stack[stack->top_stack]; // Возвращаем элемент с вершины стека
    }
}

// Печать стека
void print_stack(Stack* stack) {
    if (is_empty_stack(stack)) {
        printf("Стек пуст\n"); // Выводим сообщение, если стек пуст
        return;
    }

    printf("Стек: ");
    while (!is_empty_stack(stack)) {
        int value = pop_stack_save(stack); // Извлекаем элементы из стека для печати
        printf("%d ", value); // Печатаем извлеченные элементы
    }
    printf("\n");
}
