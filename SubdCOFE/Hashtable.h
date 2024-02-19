#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define SIZE 1000

typedef struct node_hash {
    const char* key_hash;
    const char* value_hash;
    struct node_hash* next_hash;
} Node_hash;

typedef struct {
    Node_hash* array_hash[SIZE];
} HashTable;


int hash_function(char* key);
void initialize_hash(HashTable* hashtable);
void insert_hash(HashTable* hashtable, const char* key, const char* value);
const char* getbykey_hash(HashTable* hashtable, const char* key);
void delete_hash(HashTable* hashtable, const char* key);
void printHashTable(HashTable* hashtable);
void save_table_to_file(HashTable* myTable, const char* file_name, const char* table_name);
void deletebykey_hash(HashTable* hashtable, const char* key);
#endif /* HASHTABLE_H */


