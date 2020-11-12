#include <stdlib.h>
#include <stdio.h>

#include "runtime.h"

void dispatcher() {
    int operation;

    for(;;) {
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
            /* code */
            break;
        default:
            break;
        }
    }
}