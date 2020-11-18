#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>

#include "runtime.hpp"
#include "queue.hpp"
#include "user.hpp"

void dispatcher() {
    int operation;
    int executionIndex;

    std::string currentPath;

    for(;;) {
        std::cout << currentPath << std::endl;

        if (!invariant()) {
            printf("invariant: false\n");
            printf("exit\n");
            exit(0);
        }

        forallQueue(&readyQueue, printProcess);

        printf("enter index of element to execute:\n");
        std::cin >> executionIndex;

        Process_t* currentProcess = (Process_t*) remove(&readyQueue, executionIndex);

        if (currentProcess == NULL) {
            printf("dispatcher: current process equal to null");
        }

        currentPath.append(currentProcess->processName + ", ");

        operation = contextSwitcher(currentProcess);

        switch (operation) {
            case yeild:
                enque(&readyQueue, currentProcess);
                break;
            case create:
                // to implement
                break;
            case send:
                // to implement
                break;
            case receive:
                // to implement
                break;
            default:
                break;
        }
    }
}