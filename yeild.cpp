#include "runtime.hpp"

void runtimeCall(RuntimeRequest_t* r) {
    // since the process is suspended, 
    // it's ok to use a pointer to an object on the stack
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

// warning: this call blocks
void receiveMessage(std::string sender, char* receiveBuffer) {
    RuntimeRequest_t r;
    r.requestCode = RECEIVE;
    r.sender = sender;
    r.receiveBuffer = receiveBuffer;
    runtimeCall(&r);
    return;
}

// copy sendBuffer into runtime buffer
// this will prevent the sender from modifying the message
// warning: this call blocks
void sendMessage(std::string receiver, char* sendBuffer, int sendSizeBuffer) {
    RuntimeRequest_t r;
    r.requestCode = SEND;
    r.receiver = receiver;
    r.sendBuffer = sendBuffer;
    r.sendSizeBuffer = sendSizeBuffer;
    runtimeCall(&r);
    return;
}