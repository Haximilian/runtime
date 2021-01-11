#include "runtime.hpp"

void runtimeCall(RuntimeRequest_t* r) {
    // set global variable to pointer of value on suspended process stack
    runtimeRequestStatic = r;

    asm ("\
        call runtimeEntryPoint \n\
        "
        :
        :
        :
    );
}

void yeildRuntime() {
    RuntimeRequest_t r;
    r.requestCode = YEILD;
    runtimeCall(&r);
}