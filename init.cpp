#include <stdlib.h>

#include "runtime.hpp"
#include "user.hpp"

Process_t processControlBlock[CONCURENCY];

Process_t* finalReady;
Process_t* initialReady;
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

    createProcess(sampleOneProcess);

    createProcess(sampleTwoProcess);

    createProcess(sampleThreeProcess);

    dispatcher();
}