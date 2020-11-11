#include <stdlib.h>
#include <stdio.h>

#include "runtime.h"

Process_t processControlBlock[CONCURENCY];

void initializeProcessControlBlock() {
    initialFree = processControlBlock;
    Process_t* current = processControlBlock;

    for (int i; i < CONCURENCY - 1; i++) {
        current->next = current + 1;
        current = current + 1;
    }

    current->next = NULL;
    finalFree = current;
}

void sampleOneProcess() {
    int elem;
    for (;;) {
        printf("current stack location: %p\n", &elem);
        printf("hello from p1\n", &elem);
        yeildRuntime();
    }
}

void sampleTwoProcess() {
    int elem;
    for (;;) {
        printf("current stack location: %p\n", &elem);
        printf("hello from p2\n", &elem);
        yeildRuntime();
    }
}

int main() {
    initializeProcessControlBlock();

    createProcess(sampleOneProcess);

    createProcess(sampleTwoProcess);

    dispatcher();
}