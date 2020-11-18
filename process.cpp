#include <stdio.h>

#include "runtime.hpp"

void printProcess(void* process) {
    Process_t* castProcess = (Process_t*) process;
    printf("----------\n");
    printf("identifier: %d\n", castProcess->identifier);
    printf("processName: %.*s\n", castProcess->processName.size(), castProcess->processName.c_str());
    printf("stackPointer: %p\n", castProcess->stackPointer);
    printf("----------\n");
}