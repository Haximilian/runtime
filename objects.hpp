#include <VClock.h>

template <typename T>
class rObject {
public:
    Object(VClock);
    ~Object();

    // this method updates processes vclock
    T read(VClock*);
    void write(VClock, T)

private:
    VClock v;
    T object;
};