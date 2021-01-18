#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>

#include "runtime.hpp"
#include "queue.hpp"
#include "user.hpp"

Process_t* toExecute(Queue_t* readyQueue);

void dispatcher() {
    RuntimeRequest_t* r;

    std::string currentPath;

    for(;;) {
        std::cout << stateHash() << std::endl;
        Process_t* currentProcess = toExecute(&readyQueue);

        if (currentProcess == NULL) {
            printf("dispatcher: current process equal to null");
        }

        r = contextSwitcher(currentProcess);

        switch (r->requestCode) {
            case YEILD:
                enque(&readyQueue, currentProcess);
                break;
            case CREATE:
                // to implement
                break;
            case LOCK:
                // to implement
                std::cout << "dispatcher: receive\n";
                break;
            default:
                break;
        }
    }
}

void printProcess(void* process) {
    Process_t* castProcess = (Process_t*) process;
    printf("%.*s, ", castProcess->processName.size(), castProcess->processName.c_str());
}

Process_t* toExecute(Queue_t* readyQueue) {
    forallQueue(readyQueue, printProcess);
    std::cout << std::endl;

    std::string identifier;
    std::cin >> identifier;

    Element_t* e;
    int compareResult;
    int queuePosition = 0;
    for (e = readyQueue->head; e; e = e->next) {
        compareResult = identifier.compare(((Process_t*) e->object)->processName);
        if (!compareResult) {
            remove(readyQueue, queuePosition);
            return (Process_t*) e->object;
        }
        queuePosition += 1;
    }

    return NULL;
}