#include <sys/socket.h>
#include <netinet/in.h>
#include <poll.h>

#define BACKLOG 8
#define MAXIMUM_SOCKETS 128
#define WATCH_EVENTS POLLIN

class StreamServer {
    public:
        StreamServer(
            sockaddr_in* server_address, 
            void (*request_handler)(sockaddr_in* client_address, int conn_socket));

        void serve_forever();

    private:
        sockaddr_in* server_address;
        
        int receive_socket;

        struct pollfd wait_set[MAXIMUM_SOCKETS];

        int wait_set_size;

        void add_wait_set(int socket);

        void remove_wait_set(int socket);

        void bind_server();

        void activate_server();

        int accept_request(sockaddr* client_address, socklen_t* address_length);

        void (*request_handler)(sockaddr_in* client_address, int conn_socket);

        void close_request(int connection);
};