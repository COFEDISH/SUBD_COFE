#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* extract_json_data(char* request) {
    char* json_start = strstr(request, "{");
    if (json_start == NULL) {
        printf("JSON data not found\n");
        return NULL;
    }

    char* json_end = strrchr(request, '}') + 1;
    if (json_end == NULL) {
        printf("Invalid JSON data\n");
        return NULL;
    }

    size_t json_length = json_end - json_start;
    char* json_data = (char*)malloc((json_length + 1) * sizeof(char));
    if (json_data == NULL) {
        printf("Memory allocation error\n");
        return NULL;
    }

    strncpy(json_data, json_start, json_length);
    json_data[json_length] = '\0';

    return json_data;
}

char* read_json_file(const char* filename) {
    char filepath[100];
    sprintf(filepath, "/data/%s", filename);
    FILE* file = fopen(filepath, "r");
    if (file == NULL) {
        perror("Error opening file for reading");
        return NULL;
    }

    size_t buffer_size = 1024;
    char* buffer = (char*)malloc(buffer_size * sizeof(char));
    if (buffer == NULL) {
        printf("Memory allocation error\n");
        fclose(file);
        return NULL;
    }

    buffer[0] = '\0';

    char line[1024];
    while (fgets(line, sizeof(line), file) != NULL) {
        size_t line_len = strlen(line);

        while (strlen(buffer) + line_len >= buffer_size - 1) {
            buffer_size *= 2;
            char* temp = (char*)realloc(buffer, buffer_size * sizeof(char));
            if (temp == NULL) {
                printf("Memory allocation error\n");
                free(buffer);
                fclose(file);
                return NULL;
            }
            buffer = temp;
        }

        strcat(buffer, line);
    }

    fclose(file);
    return buffer;
}

void save_json_to_file(const char* json_data, const char* filename) {
    char filepath[100];
    sprintf(filepath, "/data/%s", filename);
    FILE* file = fopen(filepath, "w");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    if (fprintf(file, "[%s]", json_data) < 0) {
        perror("Error writing to file");
    }

    fclose(file);
}
