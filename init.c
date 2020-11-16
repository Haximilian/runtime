#include <stdlib.h>

#include "runtime.h"
#include "user.h"

Process_t processControlBlock[CONCURENCY];

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