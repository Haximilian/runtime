#include "runtime.hpp"

void yeildRuntime() {
    asm ("\
        call runtimeEntryPoint \n\
        "
        :
        :
        :
    );
}