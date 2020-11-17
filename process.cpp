#include <stdlib.h>
#include <stdio.h>

#include "runtime.hpp"

// return null if nothing to deque
Process_t* dequeReady(void) {
    Process_t* toReturn = initialReady;

    if (initialReady) {
        initialReady = initialReady->next;

        if (toReturn == finalReady) {
            finalReady = NULL;
        }

        toReturn->next = NULL;
    }

    return toReturn;
}

void enqueReady(Process_t* toEnque) {
    toEnque->next = NULL;

    // check if queue is empty
    if (finalReady) {
        finalReady->next = toEnque;
    } else {
        initialReady = toEnque;
    }

    finalReady = toEnque;
}

void printProcess(Process_t* process) {
    printf("----------\n");
    printf("identifier: %d\n", process->identifier);
    printf("stackPointer: %p\n", process->stackPointer);
    printf("next: %p\n", process->next);
    printf("----------\n");
}

void printReadyQueue() {
    Process_t* curr;
    for (curr = initialReady; curr; curr = curr->next) {
        printProcess(curr);
    }
}

// add functions to serialize the queue for sending to client
// add previous pointer