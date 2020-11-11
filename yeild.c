#include "runtime.h"

void yeildRuntime() {
    void* kernelEntryPoint = runtimeEntryPoint;

    asm ("\
        jmp *%0 \n\
        "
        : "+m" (kernelEntryPoint)
        :
        :
    );
}