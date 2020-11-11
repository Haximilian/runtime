#include "runtime.h"

void yeildRuntime() {
    void* kernelEntryPoint = runtimeEntryPoint;

    asm ("\
        mov %1, %%rax \n\
        jmp *%0 \n\
        "
        : "+m" (kernelEntryPoint), "+r" (runtimeStackPointer)
        :
        :
    );
}