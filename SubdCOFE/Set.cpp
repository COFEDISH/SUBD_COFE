#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Set.h"
#include "Save_and_Output.h"
// Определение структуры Set для представления множества
// Инициализация множества
void initialize_set(Set* set) {
    set->size_set = 0; // Устанавливаем начальный размер множества 0
}

// Проверка наличия элемента в множестве
bool contains_set(Set* set, int element) {
    for (int i = 0; i < set->size_set; i++) {
        if (set->elements_set[i] == element) {
            return true; // Если элемент найден, возвращаем true
        }
    }
    return false; // Если элемент не найден, возвращаем false
}

// Добавление элемента в множество
void add_set(Set* set, int element) {
    if (!contains_set(set, element)) { // Проверяем, содержится ли уже элемент в множестве
        set->elements_set[set->size_set++] = element; // Если элемента нет, добавляем его в множество
    }
}

// Удаление элемента из множества
void remove_element_set(Set* set, int element) {
    for (int i = 0; i < set->size_set; i++) {
        if (set->elements_set[i] == element) {
            // Если элемент найден, сдвигаем остальные элементы влево, чтобы удалить данный элемент
            for (int j = i; j < set->size_set - 1; j++) {
                set->elements_set[j] = set->elements_set[j + 1];
            }
            set->size_set--; // Уменьшаем размер множества после удаления элемента
            break; // Выходим из цикла
        }
    }
}

// Печать множества
void print_set(Set* set) {
    printf("{ ");
    for (int i = 0; i < set->size_set; i++) {
        printf("%d ", set->elements_set[i]);
    }
    printf("}\n");
}


