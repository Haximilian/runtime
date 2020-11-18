#include <stdio.h>

#include "runtime.hpp"
#include "user.hpp"

int a = 0;

// return 1 if true else 0
int invariant() {
    if (a < 20) {
        return 1;
    } else {
        return 0;
    }
}

void sampleOneProcess() {
    int elem;
    for (;;) {
        // equality not +=
        a = 1;
        printf("sampleOneProcess -> a: %d\n", a);
        yeildRuntime();
    }
}

void sampleTwoProcess() {
    int elem;
    for (;;) {
        a += 5;
        printf("sampleTwoProcess -> a: %d\n", a);
        yeildRuntime();
    }
}

void sampleThreeProcess() {
    int elem;
    for (;;) {
        a += 10;
        printf("sampleThreeProcess -> a: %d\n", a);
        yeildRuntime();
    }
}