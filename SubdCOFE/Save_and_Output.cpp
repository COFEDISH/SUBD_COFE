#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Set.h"
#include "Stack.h"
#include "Queue.h"
#include "Hashtable.h"
#include "Save_and_Output.h"
#define MAX_BUFFER_SIZE 1100

// Сохранение данных всех структур в файл
// Сохранение данных множества в файл
void save_set_to_file(Set* mySet, const char* file_name, const char* table_name) {
    remove_set_from_file(file_name, table_name);
    FILE* file = fopen(file_name, "a");
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        return;
    }

    fprintf(file, "Set Data (%s):\n", table_name);
    for (int i = 0; i < mySet->size_set; i++) {
        fprintf(file, "%d\n", mySet->elements_set[i]);
    }

    fclose(file);
}
void save_stack_to_file(Stack* myStack, const char* file_name, const char* table_name) {
    int stack_array[MAX_BUFFER_SIZE];
    int index = 0;

    while (!is_empty_stack(myStack)) {
        stack_array[index++] = pop_stack_save(myStack);
    }

    remove_stack_from_file(file_name, table_name);
    FILE* file = fopen(file_name, "a");
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        return;
    }

    fprintf(file, "Stack Data (%s):\n", table_name);
    for (int i = index - 1; i >= 0; i--) {
        fprintf(file, "%d\n", stack_array[i]);
    }
    fprintf(file, "\n"); // Добавьте новую строку для отделения данных от других секций

    fclose(file);
}

//Удаление множества из файла

void remove_set_from_file(const char* file_name, const char* table_name) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        return;
    }

    FILE* temp_file = fopen("temp.data", "w");
    if (temp_file == NULL) {
        printf("Ошибка при открытии временного файла\n");
        fclose(file);
        return;
    }

    char buffer[MAX_BUFFER_SIZE];
    bool is_set_data = false;

    char header[100];
    sprintf(header, "Set Data (%s):", table_name);

    while (fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) {
        if (strstr(buffer, header) != NULL) {
            is_set_data = true;
            continue;
        }
        if (!is_set_data) {
            fprintf(temp_file, "%s", buffer);
        }
        if (is_set_data and (strstr(buffer, "Stack Data") != NULL || strstr(buffer, "Queue Data") != NULL || strstr(buffer, "Hash Table Data") != NULL)) {
            is_set_data = false;
            fprintf(temp_file, buffer);
            
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(file_name);
    rename("temp.data", file_name);
}


//Удаление стэка из файла
void remove_stack_from_file(const char* file_name, const char* table_name) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        return;
    }

    FILE* temp_file = fopen("temp.data", "w");
    if (temp_file == NULL) {
        printf("Ошибка при открытии временного файла\n");
        fclose(file);
        return;
    }

    char buffer[MAX_BUFFER_SIZE];
    bool is_stack_data = false;

    char header[100];
    sprintf(header, "Stack Data (%s):", table_name);

    while (fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) {
        if (strstr(buffer, header) != NULL) {
            is_stack_data = true;
            continue;
        }
        if (!is_stack_data) {
            fprintf(temp_file, "%s", buffer);
        }
        if (is_stack_data && (strstr(buffer, "Set Data") != NULL || strstr(buffer, "Queue Data") != NULL || strstr(buffer, "Hash Table Data") != NULL)) {
            is_stack_data = false;
            fprintf(temp_file, buffer);
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(file_name);
    rename("temp.data", file_name);
}


// Сохранение данных очереди в файл
void save_queue_to_file(Queue* myQueue, const char* file_name, const char* table_name) {
    remove_queue_from_file(file_name, table_name);
    FILE* file = fopen(file_name, "a");
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        return;
    }

    fprintf(file, "Queue Data (%s):\n", table_name);
    Queue tempQueue = *myQueue;
    while (!is_empty_queue(&tempQueue)) {
        fprintf(file, "%d\n", dequeue(&tempQueue));
    }

    fclose(file);
}

void remove_queue_from_file(const char* file_name, const char* table_name) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        return;
    }

    FILE* temp_file = fopen("temp.data", "w");
    if (temp_file == NULL) {
        printf("Ошибка при открытии временного файла\n");
        fclose(file);
        return;
    }

    char buffer[MAX_BUFFER_SIZE];
    bool is_queue_data = false;

    char header[100];
    sprintf(header, "Queue Data (%s):", table_name);

    while (fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) {
        if (strstr(buffer, header) != NULL) {
            is_queue_data = true;
            continue;
        }
        if (!is_queue_data) {
            fprintf(temp_file, "%s", buffer);
        }
        if (is_queue_data && (strstr(buffer, "Stack Data") != NULL || strstr(buffer, "Set Data") != NULL || strstr(buffer, "Hash Table Data") != NULL)) {
            is_queue_data = false;
            fprintf(temp_file, buffer);
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(file_name);
    rename("temp.data", file_name);
}


// Чтение данных множества из файла
Set read_set_from_file(const char* file_name, const char* table_name) {
    Set mySet;
    initialize_set(&mySet);
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        return mySet;
    }

    char buffer[MAX_BUFFER_SIZE];
    bool is_set_data = false;

    char header[100];
    sprintf(header, "Set Data (%s):", table_name);

    while (fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) {
        if (strstr(buffer, header) != NULL) {
            is_set_data = true;
            continue;
        }
        if (is_set_data) {
            if (strstr(buffer, "Stack Data") != NULL || strstr(buffer, "Queue Data") != NULL || strstr(buffer, "Hash Table Data") != NULL) {
                break;
            }
            // Парсинг и обработка данных множества
            int element;
            if (sscanf(buffer, "%d", &element) == 1) {
                add_set(&mySet, element);
            }
        }
    }
    fclose(file);
    return mySet;
}



// Чтение данных стека из файла
Stack read_stack_from_file(const char* file_name, const char* table_name) {
    Stack myStack;
    initialize_stack(&myStack);
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        return myStack;
    }

    char buffer[MAX_BUFFER_SIZE];
    bool is_stack_data = false;
    int values[MAX_SIZE];
    int values_count = 0;

    char header[100];
    sprintf(header, "Stack Data (%s):", table_name);

    while (fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) {
        if (strstr(buffer, header) != NULL) {
            is_stack_data = true;
            continue;
        }
        if (is_stack_data) {
            if (strstr(buffer, "Queue Data") != NULL || strstr(buffer, "Hash Table Data") != NULL || strstr(buffer, "Set Data") != NULL) {
                break;
            }
            // Обработка данных стека
            int value;
            if (sscanf(buffer, "%d", &value) == 1) {
                values[values_count] = value;
                values_count++;
            }
        }
    }

    fclose(file);

    // Заполнение стека значениями в прямом порядке
    for (int i = 0; i < values_count; i++) {
        push_stack(&myStack, values[i]);
    }

    return myStack;
}



// Чтение данных очереди из файла
Queue read_queue_from_file(const char* file_name, const char* table_name) {
    Queue myQueue;
    initialize_queue(&myQueue);
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        return myQueue;
    }

    char buffer[MAX_BUFFER_SIZE];
    bool is_queue_data = false;

    char header[100];
    sprintf(header, "Queue Data (%s):", table_name);

    while (fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) {
        if (strstr(buffer, header) != NULL) {
            is_queue_data = true;
            continue;
        }
        if (is_queue_data) {
            if (strstr(buffer, "Stack Data") != NULL || strstr(buffer, "Set Data") != NULL || strstr(buffer, "Hash Table Data") != NULL) {
                break;
            }
            // Обработка данных очереди
            int value;
            if (sscanf(buffer, "%d", &value) == 1) {
                enqueue(&myQueue, value);
            }
        }
    }

    fclose(file);
    return myQueue;
}

// Чтение данных хэш-таблицы из файла
HashTable read_table_from_file(const char* file_name, const char* table_name) {
    HashTable myTable;
    initialize_hash(&myTable);
    char filepath[100];
    sprintf(filepath, "/data/%s", file_name);
    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        printf("Ошибка при открытии файла\n");
        return myTable;
    }

    char buffer[MAX_BUFFER_SIZE];
    bool is_table_data = false;

    char header[100];
    sprintf(header, "Hash Table Data (%s):", table_name);

    while (fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) {
        if (strstr(buffer, header) != NULL) {
            is_table_data = true;
            continue;
        }
        if (is_table_data) {
            if (strstr(buffer, "Stack Data") != NULL || strstr(buffer, "Set Data") != NULL || strstr(buffer, "Queue Data") != NULL) {
                break;
            }
            // Обработка данных хэш-таблицы
            char key[20];
            char value[150000];
            if (sscanf(buffer, "%s %s", key, value) == 2) {
                insert_hash(&myTable, key, value);
            }
        }
    }

    fclose(file);
    return myTable;
}


//Удаление хеш-таблицы из файла
void remove_table_from_file(const char* file_name, const char* table_name) {
    FILE* file = fopen(file_name, "r");
    if (file == NULL) {

        return;
    }

    FILE* temp_file = fopen("temp.data", "w");
    if (temp_file == NULL) {
        printf("Ошибка при открытии временного файла\n");
        fclose(file);
        return;
    }

    char buffer[MAX_BUFFER_SIZE];
    bool is_table_data = false;

    char header[100];
    sprintf(header, "Hash Table Data (%s):", table_name);

    while (fgets(buffer, MAX_BUFFER_SIZE, file) != NULL) {
        if (strstr(buffer, header) != NULL) {
            is_table_data = true;
            continue;
        }
        if (!is_table_data) {
            fprintf(temp_file, "%s", buffer);
        }
        if (is_table_data && (strstr(buffer, "Stack Data") != NULL || strstr(buffer, "Set Data") != NULL || strstr(buffer, "Queue Data") != NULL)) {
            is_table_data = false;
            fprintf(temp_file, buffer);
        }
    }

    fclose(file);
    fclose(temp_file);

    remove(file_name);
    rename("temp.data", file_name);
}





