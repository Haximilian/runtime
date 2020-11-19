#include <stdlib.h>
#include <stdio.h>

#include <iostream>
#include <string>

#include "runtime.hpp"
#include "queue.hpp"
#include "user.hpp"

void dispatcher() {
    RuntimeRequest_t* r;
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

        r = contextSwitcher(currentProcess);


        switch (r->requestCode) {
            case YEILD:
                enque(&readyQueue, currentProcess);
                break;
            case CREATE:
                // to implement
                break;
            case SEND:
                // to implement
                std::cout << "dispatcher: receive\n";
                break;
            case RECEIVE:
                // to implement
                std::cout << "dispatcher: send\n";
                break;
            default:
                break;
        }
    }
}