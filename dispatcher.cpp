#include <stdlib.h>
#include <stdio.h>

#include "runtime.hpp"
#include "user.hpp"

void dispatcher() {
    int operation;

    for(;;) {
        if (!invariant()) {
            printf("invariant: false\n");
            printf("exit\n");
            exit(0);
        }

        printReadyQueue();

        printf("waiting for user to hit enter to continue executing\n");
        getchar();

        Process_t* currentProcess = dequeReady();

        if (currentProcess == NULL) {
            printf("dispatcher: current process equal to null");
        }

        operation = contextSwitcher(currentProcess);

        switch (operation)
        {
        case yeild:
            enqueReady(currentProcess);
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