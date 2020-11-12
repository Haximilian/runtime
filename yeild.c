#include "runtime.h"

void yeildRuntime() {
    asm ("\
        call runtimeEntryPoint \n\
        "
        :
        :
        :
    );
}