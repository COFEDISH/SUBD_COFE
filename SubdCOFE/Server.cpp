#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <pthread.h>
#include <wchar.h>
#include <locale.h>

#include "query.h" // Ваш заголовочный файл query.h

#define PORT 6379
#define START_REQUEST_BUFFER 20000

pthread_mutex_t mutex;
int current_request_index = 0;

void send_all(int socket, const char* buffer, size_t length) {
    size_t total_sent = 0;
    while (total_sent < length) {
        ssize_t sent = send(socket, buffer + total_sent, length - total_sent, 0);
        if (sent == -1) {
            // Ошибка отправки
            break;
        }
        total_sent += sent;
    }
}



void* ClientHandler(void* socket) {
    pthread_mutex_lock(&mutex);
    int client_socket = *((int*)socket);
    wchar_t* recv_buffer = (wchar_t*)malloc(START_REQUEST_BUFFER * sizeof(wchar_t));
    if (recv_buffer == NULL) {
        perror("Ошибка выделения памяти для recv_buffer");
        close(client_socket);
        pthread_mutex_unlock(&mutex);
        return NULL;
    }

    int recv_size;
    while ((recv_size = recv(client_socket, recv_buffer, START_REQUEST_BUFFER * sizeof(wchar_t), 0)) > 0) {
        recv_buffer[recv_size / sizeof(wchar_t)] = L'\0';

            size_t src_len = wcslen((const wchar_t*)recv_buffer);
            wchar_t* input_string = (wchar_t*)malloc((src_len + 1) * sizeof(wchar_t));
            if (input_string == NULL) {
                perror("Ошибка выделения памяти для input_string");
                free(recv_buffer);
                close(client_socket);
                pthread_mutex_unlock(&mutex);
                return NULL;
            }
            wcscpy(input_string, recv_buffer);

            const char* answer = get_to_subd((const unsigned char*)input_string);

            if (strcmp(answer, "Is not exist") != 0 && strcmp(answer, "Invalid query format.") != 0)
                send_all(client_socket, answer, strlen(answer));
            else
                break;

            free(input_string);
    }

    free(recv_buffer);
    close(client_socket);
    pthread_mutex_unlock(&mutex);
    return NULL;
}


int main() {
    int s, new_socket;
    struct sockaddr_in server, client;
    socklen_t c;
    pthread_t thread;

    if (pthread_mutex_init(&mutex, NULL) != 0) {
        printf("Mutex initialization failed\n");
        return 1;
    }

    printf("\nInitializing socket...\n");
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        printf("Socket creation failed\n");
        return 1;
    }
    printf("Socket created.\n");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    if (bind(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Bind failed\n");
        return 1;
    }
    printf("Bind done\n");

    if (listen(s, 3) < 0) {
        printf("Listen failed\n");
        return 1;
    }
    printf("Waiting for incoming connections...\n");

    c = sizeof(struct sockaddr_in);

    while ((new_socket = accept(s, (struct sockaddr*)&client, &c)) > 0) {
        printf("\nConnection accepted\n");
        if (pthread_create(&thread, NULL, ClientHandler, (void*)&new_socket) < 0) {
            printf("Thread creation failed\n");
            return 1;
        }
        // close(new_socket); // Закрытие сокета после обработки
    }
    close(new_socket); // Закрытие сокета после завершения обработки всех запросов

    if (new_socket < 0) {
        printf("Accept failed\n");
        return 1;
    }

    close(s);

    return 0;
}

