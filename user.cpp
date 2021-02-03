#include <stdio.h>

#include "runtime.hpp"
#include "user.hpp"

#include "VClock.h"

template <typename T>
class rObject {
public:
    rObject(T);

    // this method updates processes vclock
    T read(VClock*);
    void write(VClock*, T);

    // a user process should never use this to get a value
    // only use this to get the value to compute the state hash
    T getValueForHash();
private:
    VClock v;
    T object;
};


template <typename T>
rObject<T>::rObject(T value) {
    this->v = VClock();
    this->object = value;
}


template <typename T>
T rObject<T>::read(VClock* p) {
    (*p).merge(this->v);
    return this->object;
}

template <typename T>
void rObject<T>::write(VClock* p, T value) {
    this->v.merge(*p);
    this->object = value;
}

template <typename T>
T rObject<T>::getValueForHash() {
    return this->object;
}

rObject<int> a(0);
rObject<int> b(0);

int stateHash() {
    int result = 17;
    result = result * 31 + a.getValueForHash();
    result = result * 31 + b.getValueForHash();
    return result;
}

__cdecl void sampleOneProcess(Process_t* self) {
    // after the context is popped of then wrongfully arg is pushed and the ret addr
    self = *(&self + 3);

    int elem;
    for (;;) {
        elem = a.read(&(self->vclock));
        elem += 3;
        a.write(&(self->vclock), elem);
        yeildRuntime();
    }
}

__cdecl void sampleTwoProcess(Process_t* self) {
    // after the context is popped of then wrongfully arg is pushed and the ret addr
    self = *(&self + 3);

    int elem;
    for (;;) {
        elem = a.read(&(self->vclock));
        elem *= 5;
        a.write(&(self->vclock), elem);
        yeildRuntime();
    }
}

__cdecl void sampleThreeProcess(Process_t* self) {
    // after the context is popped of then wrongfully arg is pushed and the ret addr
    self = *(&self + 3);
    
    int elem;
    for (;;) {
        elem = b.read(&(self->vclock));
        elem += 10;
        b.write(&(self->vclock), elem);
        yeildRuntime();
    }
}
