#include <stdio.h>

#include "runtime.hpp"
#include "user.hpp"

int a = 1;
int b = 1;

// return 1 if true else 0
int invariant() {
    if (a < 20) {
        return 1;
    } else {
        return 0;
    }
}

int stateHash() {
    int result = 17;
    result = result * 31 + a;
    result = result * 31 + b;
    return result;
}

void sampleOneProcess() {
    int elem;
    for (;;) {
        // equality not +=
        a += 3;
        // printf("sampleOneProcess -> a: %d\n", a);
        yeildRuntime();
    }
}

void sampleTwoProcess() {
    int elem;
    for (;;) {
        a *= 5;
        // printf("sampleTwoProcess -> a: %d\n", a);
        yeildRuntime();
    }
}

void sampleThreeProcess() {
    int elem;
    for (;;) {
        b += 10;
        // printf("sampleThreeProcess -> a: %d\n", a);
        yeildRuntime();
    }
}