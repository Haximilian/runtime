#pragma once

typedef struct Element {
    struct Element* next;
    struct Element* prev;
    void* object;
} Element_t;

typedef struct Queue {
    struct Element* head;
    struct Element* tail;
    unsigned int size;
} Queue_t;

void initQueue(Queue_t* queue);
void enque(Queue_t* queue, void* value);
void* dequeue(Queue_t* queue);
void* remove(Queue_t* queue, int i);
void forallQueue(Queue_t* queue, void (*function)(void*));