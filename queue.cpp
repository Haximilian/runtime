#include <stdlib.h>
#include <iostream>
#include "queue.hpp"

void initQueue(Queue_t* queue) {
    queue->head = NULL;
    queue->tail = NULL;
    queue->size = 0;
    return;
}

int isEmpty(Queue_t* queue) {
    return (queue->size > 0);
}

void enque(Queue_t* queue, void* value) {
    Element_t* element = (Element_t*) malloc(sizeof(Element_t));
    element->object = value;

    element->next = NULL;
    element->prev = queue->tail;

    if (queue->tail && queue->head) {
        queue->tail->next = element;
    } else if (!queue->tail && !queue->head) {
        queue->head = element;
    } else {
        std::cout << "queue error\n";
        exit(0);
    }

    queue->tail = element;

    queue->size++;

    return;
}

void* dequeue(Queue_t* queue) {
    return remove(queue, 0);
}

void* remove(Queue_t* queue, int i) {
    if (queue->size <= i) {
        // i out of bounds
        return NULL;
    }

    Element_t* curr = queue->head;
    int counter = 0;
    for (; curr && (counter != i); curr = curr->next, counter++) {}

    if (curr->prev) {
        curr->prev->next = curr->next;
    } else {
        queue->head = curr->next;
    }

    if (curr->next) {
        curr->next->prev = curr->prev;
    } else {
        queue->tail = curr->prev;
    }

    void* toReturn = curr->object;
    free(curr);

    queue->size--;

    return toReturn;
}

// use this to print elements in a queue
void forallQueue(Queue_t* queue, void (*function)(void*)) {
    Element_t* curr;
    for (curr = queue->head; curr; curr = curr->next) {
        function(curr->object);
    }
}
