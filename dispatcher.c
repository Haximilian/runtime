#include "runtime.h"

void dispatcher() {
    int operation;

    for(;;) {
        Process_t* currentProcess = dequeReady();

        operation = contextSwitcher(currentProcess);

        switch (operation)
        {
        case yeild:
            /* code */
            break;
        case create:
            /* code */
            break;
        default:
            break;
        }
    }
}