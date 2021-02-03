#include "objects.hpp"
#include <VClock.h>

template <typename T>
rObject::rObject(VClock initialClock, T value) {
    this.v = initialClock;
    this.object = value;
}

template <typename T>
T rObject::read(VClock* p) {
    (*p).merge(this.v);
    return this.object;
}

template <typename T>
void rObject::write(VClock* p, T value) {
    this.v.merge(*p);
    this.object = value;
}