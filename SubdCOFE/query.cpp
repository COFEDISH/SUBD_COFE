#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Set.h"
#include "Save_and_Output.h"
#include <locale.h>
#include "json_files.h"

char tokens[] = "7HbN3P#m9e6@kT2d123dNEar";
char tokens_admin[] = "R#f7GhT9@Lp2$y5BqZx!0*D";

char** split_string(unsigned char* input_string_un) {
    size_t src_len = strlen((const char*)input_string_un);
    char* input_string = (char*)malloc(src_len + 1); // выделяем память для копии

    strcpy(input_string, (const char*)input_string_un); // копируем из unsigned char* в char*

    char** result = (char**)malloc(2 * sizeof(char*));
    result[0] = NULL;
    result[1] = NULL;
    const char* space_pos = strchr(input_string, ' ');
    if (space_pos != NULL) {
        size_t token_len = space_pos - input_string;
        result[0] = (char*)malloc(token_len + 1);
        strncpy(result[0], input_string, token_len);
        result[0][token_len] = '\0';

        size_t query_len = strlen(input_string) - token_len - 1;
        result[1] = (char*)malloc(query_len + 1);
        strncpy(result[1], space_pos + 1, query_len);
        result[1][query_len] = '\0';
    }
    else {
        result[0] = strdup(input_string);
        result[1] = strdup("");
    }

    return result;
}


const char* int_to_string(int value) {
    // Выберите достаточно большой буфер для вашего случая
    static char buffer[20]; // Например, для 64-битного int

    // Преобразуйте int в строку
    snprintf(buffer, sizeof(buffer), "%d", value);

    return buffer;
}


// Функция для проверки строки на соответствие шаблону
bool check_string_format(const char* input_str) {
    char file_name[256];
    char query_str[110000];

    // Общий шаблон для строки
    if (sscanf(input_str, "--file %255s --query '%255[^']'", file_name, query_str) != 2) {
        return false;  // Не удалось разобрать строку
    }

    // Шаблон для QUERY = HSET
    if (strncmp(query_str, "HSET", 4) != 0) {
        return true;  // Строка соответствует общему формату
    }

    // Шаблон для QUERY = HSET
    if (strncmp(query_str, "HSET", 4) == 0) {
        char set_name[256];
        char key[256];
        char value[150000];

        if (sscanf(query_str, "HSET %s %s %s", set_name, key, value) != 3) {
            return false;  // Не удалось разобрать HSET запрос
        }
    }
    else if (strncmp(query_str, "GSON", 4) == 0) {
        char command[256];
        char argument[256];

        if (sscanf(query_str, "GSON %s", command) != 1) {
            return false; // Не удалось разобрать GSON запрос
        }
    }

    return true;  // Строка соответствует формату HSET или GSON
}

const char* get_to_subd(unsigned char* query_crypt) {
    char** result = split_string(query_crypt);
    const char* token = result[0];
    char* query = result[1];
    if (!check_string_format(query)) return "Invalid query format.";

    if (strstr(query, "SADD") != NULL) {
        int element;
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'SADD %s %d'", filename, table_name, &element);
        const char* c_filename = filename;
        const char* c_table_name = table_name;
        Set Set = read_set_from_file(filename, table_name);
        add_set(&Set, element);
        save_set_to_file(&Set, filename, table_name);
        return "Complete";
    }
    else if (strstr(query, "SREM") != NULL) {
        int element;
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'SREM %s %d'", filename, table_name, &element);
        Set Set = read_set_from_file(filename, table_name);
        remove_element_set(&Set, element);
        save_set_to_file(&Set, filename, table_name);
        return "Complete";
    }
    else if (strstr(query, "SISMEMBER") != NULL) {
        int element;
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'SISMEMBER %s %d'", filename, table_name, &element);
        Set Set = read_set_from_file(filename, table_name);
        if (contains_set(&Set, element)) printf("-> %s", "True");
        else printf("-> %s", "False");
    }

    else if (strstr(query, "SISSHOW") != NULL) {
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'SISSHOW %[^\']'", filename, table_name);
        Set mySet = read_set_from_file(filename, table_name);
        print_set(&mySet);

    }

    else if (strstr(query, "SPUSH") != NULL) {
        int element;
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'SPUSH %s %d'", filename, table_name, &element);
        Stack Stack = read_stack_from_file(filename, table_name);
        push_stack(&Stack, element);
        save_stack_to_file(&Stack, filename, table_name);
        return "Complete";
    }

    else if (strstr(query, "SPOP") != NULL) {
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'SPOP %s'", filename, table_name);
        Stack Stack = read_stack_from_file(filename, table_name);
        return int_to_string(top_stack(&Stack));
        pop_stack(&Stack, filename, table_name);

    }

    else if (strstr(query, "STACKSHOW") != NULL) {
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'STACKSHOW %[^\']'", filename, table_name);
        Stack Stack = read_stack_from_file(filename, table_name);
        print_stack(&Stack);
    }


    else if (strstr(query, "QPUSH") != NULL) {
        int element;
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'QPUSH %s %d'", filename, table_name, &element);
        Queue Queue = read_queue_from_file(filename, table_name);
        enqueue(&Queue, element);
        save_queue_to_file(&Queue, filename, table_name);
        return "Complete";
    }

    else if (strstr(query, "QPOP") != NULL) {
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'QPOP %s'", filename, table_name);
        Queue Queue = read_queue_from_file(filename, table_name);
        return int_to_string(top_queue(&Queue));
        dequeue(&Queue);
        save_queue_to_file(&Queue, filename, table_name);

    }

    else if (strstr(query, "QSHOW") != NULL) {
        char filename[20], table_name[20];
        sscanf(query, "--file %s --query 'QSHOW %[^\']'", filename, table_name);
        Queue Queue = read_queue_from_file(filename, table_name);
        print_queue(&Queue);
    }

    else if (strstr(query, "HSET") != NULL) {
        char element[110000], key[20], filename[20], table_name[20];
        sscanf(query, "--file %s --query 'HSET %s %s %[^\']'", filename, table_name, key, &element);
        const char* c_filename = filename;
        const char* c_table_name = table_name;
        const char* c_key = key;
        const char* c_element = element;
        HashTable HS;
        HS = read_table_from_file(filename, table_name);
        insert_hash(&HS, c_key, c_element);
        save_table_to_file(&HS, filename, table_name);
        return "Complete";
    }

    else if (strstr(query, "HDEL") != NULL) {
        char key[20], filename[20], table_name[20];
        sscanf(query, "--file %s --query 'HDEL %s %[^\']'", filename, table_name, key);
        const char* c_filename = filename;
        const char* c_table_name = table_name;
        const char* c_key = key;
        HashTable HS;
        HS = read_table_from_file(filename, table_name);
        deletebykey_hash(&HS, c_key);
        save_table_to_file(&HS, filename, table_name);
        return "Complete";
    }


    else if (strstr(query, "HGET") != NULL) {
        char key[20], filename[20], table_name[20];
        sscanf(query, "--file %s --query 'HGET %s %[^\']'", filename, table_name, key);
        HashTable HS = read_table_from_file(filename, table_name);
        const char* value = getbykey_hash(&HS, key);
        if (value != NULL) {
            return value;
        }
        else {
            return "Is not exist";
        }
    }

    else if (strstr(query, "GSON save") != NULL) {

        char filename[20];
        sscanf(query, "--file %s --query", filename);
        printf(filename);
        if ((strcmp(filename, "Pharmacies.json") != 0 and strcmp(filename, "Medicine.json") != 0)) {
            save_json_to_file(extract_json_data(query), filename);
            return "Complete";

        }
        else {
            if (strcmp(token, tokens_admin) == 0) {
                save_json_to_file(extract_json_data(query), filename);
                return "Complete";
            }
            else {
                return "Invalid Token";
            }
        }

    }

    else if (strstr(query, "GSON get") != NULL) {
        char filename[20];
        sscanf(query, "--file %s --query", filename);
        if ((strcmp(filename, "Pharmacies.json") != 0 and strcmp(filename, "Medicine.json") != 0)) {
            return read_json_file(filename);
        }
        else {
            if (strcmp(token, tokens) == 0) {
                return read_json_file(filename);
            }
            else {
                return "Invalid Token";
            }
        }

    }

}

