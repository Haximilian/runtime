#include <string>

// use union
typedef struct RuntimeRequest {
    int requestCode;
    std::string sender;
    char* receiveBuffer;
    std::string receiver;
    char* sendBuffer;
    int sendSizeBuffer;
} RuntimeRequest_t;