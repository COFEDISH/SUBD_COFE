#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_SIZE 100

typedef struct {
    int elem_queue[MAX_SIZE];
    int front;
    int rear;
    int size_queue;
} Queue;

void initialize_queue(Queue* queue);
bool is_empty_queue(Queue* queue);
bool is_full_queue(Queue* queue);
void enqueue(Queue* queue, int value);
int dequeue(Queue* queue);
int top_queue(Queue* queue);
void print_queue(Queue* queue);

#endif /* QUEUE_H */

