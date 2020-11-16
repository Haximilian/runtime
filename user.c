#include <stdio.h>

#include "runtime.h"
#include "user.h"

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
        printf("stack pointer: %p\n", &elem);
        printf("hello from p1\n");
        a += 1;
        printf("a: %d\n", a);
        yeildRuntime();
    }
}

void sampleTwoProcess() {
    int elem;
    for (;;) {
        printf("stack pointer: %p\n", &elem);
        printf("hello from p2\n");
        a += 5;
        printf("a: %d\n", a);
        yeildRuntime();
    }
}

void sampleThreeProcess() {
    int elem;
    for (;;) {
        printf("stack pointer: %p\n", &elem);
        printf("hello from p3\n");
        a += 10;
        printf("a: %d\n", a);
        yeildRuntime();
    }
}