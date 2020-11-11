#include "runtime.h"

#include <stdlib.h>

// return null if nothing to deque
Process_t* dequeReady(void) {
    Process_t* toReturn = initialReady;

    if (initialReady) {
        initialReady = initialReady->next;

        if (toReturn == finalReady) {
            finalReady = NULL;
        }

        toReturn->next = NULL;
    }

    return toReturn;
}

void enqueReady(Process_t* toEnque) {
    toEnque->next = NULL;

    // check if queue is empty
    if (finalReady) {
        finalReady->next = toEnque;
    } else {
        initialReady = toEnque;
    }

    finalReady = toEnque;
}