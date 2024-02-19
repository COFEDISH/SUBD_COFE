#ifndef Save_and_Output_h
#define Save_and_Output_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Set.h"
#include "Stack.h"
#include "Queue.h"
#include "Hashtable.h"

#define MAX_BUFFER_SIZE 20

void save_set_to_file(Set* mySet, const char* file_name, const char* table_name);
void save_stack_to_file(Stack* myStack, const char* file_name, const char* table_name);
void save_queue_to_file(Queue* myQueue, const char* file_name, const char* table_name);
void remove_set_from_file(const char* file_name, const char* table_name);
void remove_stack_from_file(const char* file_name, const char* table_name);
void remove_queue_from_file(const char* file_name, const char* table_name);
void remove_table_from_file(const char* file_name, const char* table_name);
Set read_set_from_file(const char* file_name, const char* table_name);
Stack read_stack_from_file(const char* file_name, const char* table_name);
Queue read_queue_from_file(const char* file_name, const char* table_name);
HashTable read_table_from_file(const char* file_name, const char* table_name);

#endif

