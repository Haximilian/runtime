#include <stdlib.h>
#include <stdio.h>

#include <string>

#include "queue.hpp"
#include "runtime.hpp"

void createProcess(void (*jumpTo)(void), std::string processName = "") {
    Process_t* toReturn = dequeFree();

    // check if process control block was succesfully allocated
    if (!toReturn) {
        printf("createProcess: dequeFree return value equal to null\n");
        exit(0);
    }

    toReturn->processName = processName;

    // architecture:
    // stack grows towards lower addresses
    toReturn->stackPointer = (char*) malloc(STACKSIZE) + STACKSIZE;
    toReturn->stackPointer = (char*) toReturn->stackPointer - sizeof(Context_t);

    // initialize context
    ((Context_t*) toReturn->stackPointer)->instructionPointer = (void*) jumpTo;

    enque(&readyQueue, toReturn);
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