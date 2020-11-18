#include <stdlib.h>
#include <string>
#include "runtime.hpp"
#include "user.hpp"

Process_t processControlBlock[CONCURENCY];

Queue_t readyQueue;
Process_t* finalFree;
Process_t* initialFree;

void* runtimeStackPointer;

void initializeProcessControlBlock() {
    initialFree = processControlBlock;
    Process_t* current = processControlBlock;

    for (int i = 0; i < CONCURENCY - 1; i++) {
        // initialize identifier
        current->identifier = i;

        current->next = current + 1;
        current = current + 1;
    }

    current->next = NULL;
    finalFree = current;
}

int main() {
    initializeProcessControlBlock();

    initQueue(&readyQueue);

    createProcess(sampleOneProcess, "Alpha");

    createProcess(sampleTwoProcess, "Beta");

    createProcess(sampleThreeProcess, "Delta");

    dispatcher();
}