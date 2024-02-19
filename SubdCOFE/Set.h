#ifndef SET_H
#define SET_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int elements_set[100];
    int size_set;
} Set;

void initialize_set(Set* set);
bool contains_set(Set* set, int value);
void add_set(Set* set, int value);
void remove_element_set(Set* set, int value);
void print_set(Set* set);
void destroy_set(Set* set);

#endif /* SET_H */

