#ifndef LIST_H
#define LIST_H

struct List {
    const char* data_list;
    struct List* next_list;
};

extern struct List* head_list;

void insert(char* value);

#endif
