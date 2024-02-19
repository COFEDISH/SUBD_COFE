#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "List.h"

// Вставка в начало списка
void insert(char* value) {
    struct List* newList = (struct List*)malloc(sizeof(struct List));
    newList->data_list = (char*)malloc((strlen(value) + 1) * sizeof(char));
    value = _strdup(newList->data_list);
    newList->next_list = head_list;
    head_list = newList;
}





