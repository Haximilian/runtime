#include <stdlib.h>
#include <stdio.h>

#include <string>

#include "queue.hpp"
#include "runtime.hpp"

void createProcess(void (*jumpTo)(Process_t*), std::string processName = "") {
    Process_t* p = dequeFree();

    // check if process control block was succesfully allocated
    if (!p) {
        printf("createProcess: dequeFree return value equal to null\n");
        exit(0);
    }

    p->processName = processName;

    // architecture:
    // stack grows towards lower addresses
    p->stackPointer = (char*) malloc(STACKSIZE) + STACKSIZE;

    // user defined thread method takes a pointer as an argument
    p->stackPointer = (char*) p->stackPointer - sizeof(Process_t*);
    *((Process_t**) p->stackPointer) = p;

    p->stackPointer = (char*) p->stackPointer - sizeof(Context_t);

    // initialize context
    ((Context_t*) p->stackPointer)->instructionPointer = (void*) jumpTo;

    enque(&readyQueue, p);
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