#include <stdlib.h>
#include <stdio.h>

#include "runtime.h"

void createProcess(void (*jumpTo)(void)) {
    Process_t* toReturn = dequeFree();

    // check if process control block was succesfully allocated
    if (!toReturn) {
        printf("createProcess: dequeFree return value equal to null\n");
        exit(0);
    }

    // architecture:
    // stack grows towards lower addresses
    toReturn->stackPointer = malloc(STACKSIZE) + STACKSIZE;
    toReturn->stackPointer -= sizeof(Context_t);

    // initialize context
    ((Context_t*) toReturn->stackPointer)->instructionPointer = jumpTo;

    enqueReady(toReturn);
}

// return null if nothing to deque
Process_t* dequeFree(void) {
    Process_t* toReturn = initialFree;

    if (initialFree) {
        initialFree = initialFree->next;

        if (toReturn == finalFree) {
            finalFree = NULL;
        }

        toReturn->next = NULL;
    }

    return toReturn;
}

void enqueFree(Process_t* toEnque) {
    toEnque->next = NULL;

    // check if queue is empty
    if (finalFree) {
        finalFree->next = toEnque;
    } else {
        initialFree = toEnque;
    }

    finalFree = toEnque;
}