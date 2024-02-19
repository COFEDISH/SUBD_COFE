#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Queue.h"
#define MAX_SIZE 100



// Инициализация очереди
void initialize_queue(Queue* queue) {
    queue->size_queue = 0;
    queue->front = 0;
    queue->rear = -1;
}

// Проверка на пустоту очереди
bool is_empty_queue(Queue* queue) {
    return queue->size_queue == 0;
}

// Проверка на полноту очереди
bool is_full_queue(Queue* queue) {
    return queue->size_queue == MAX_SIZE;
}

// Добавление элемента в очередь
void enqueue(Queue* queue, int value) {
    if (is_full_queue(queue)) {
        printf("Очередь переполнена\n");
    }
    else {
        queue->rear = (queue->rear + 1) % MAX_SIZE;
        queue->elem_queue[queue->rear] = value;
        queue->size_queue++;
    }
}

// Извлечение элемента из очереди
int dequeue(Queue* queue) {
    if (is_empty_queue(queue)) {
        printf("Очередь пуста\n");
        return -1;
    }
    else {
        int value = queue->elem_queue[queue->front];
        queue->front = (queue->front + 1) % MAX_SIZE;
        queue->size_queue--;
        return value;
    }
}

// Получение первого элемента из очереди без его удаления
int top_queue(Queue* queue) {
    if (is_empty_queue(queue)) {
        printf("Очередь пуста\n");
        return -1;
    }
    else {
        return queue->elem_queue[queue->front];
    }
}

// Печать очереди
void print_queue(Queue* queue) {
    if (is_empty_queue(queue)) {
        printf("Очередь пуста\n");
        return;
    }

    printf("Очередь: ");
    Queue tempQueue;
    initialize_queue(&tempQueue);

    while (!is_empty_queue(queue)) {
        int value = dequeue(queue);
        printf("%d ", value);
        enqueue(&tempQueue, value);
    }

    while (!is_empty_queue(&tempQueue)) {
        enqueue(queue, dequeue(&tempQueue)); // Восстановление изначальной очереди
    }

    printf("\n");
}


