#include <cstring>

#include <unistd.h>
#include <cassert>
#include "server.hpp"

StreamServer::StreamServer(
    sockaddr_in* server_address, 
    void (*request_handler)(sockaddr_in* client_address, int conn_socket)) 
{
    this->receive_socket = socket(AF_INET, SOCK_STREAM, 0);
    
    this->wait_set_size = 0;
    memset(this->wait_set, 0xFF, MAXIMUM_SOCKETS * sizeof(struct pollfd));
    add_wait_set(receive_socket);

    this->request_handler = request_handler;
    this->server_address = server_address;

    bind_server();
    activate_server();
}

void StreamServer::add_wait_set(int socket)
{
    assert(wait_set_size < MAXIMUM_SOCKETS);
    
    for (int i = 0; i < MAXIMUM_SOCKETS; i++) {
        if (this->wait_set[i].fd == -1) {
            this->wait_set[i].fd = socket;
            this->wait_set[i].events = WATCH_EVENTS;
            this->wait_set[i].revents = 0;

            this->wait_set_size++;

            return;
        }
    }
}

void StreamServer::remove_wait_set(int socket)
{
    for (int i = 0; i < MAXIMUM_SOCKETS; i++) {
        if (this->wait_set[i].fd == socket) {
            this->wait_set[i].fd = -1;

            this->wait_set_size--;

            return;
        }
    }
}

void StreamServer::serve_forever()
{
    while (true) {
        // allocate on stack
        // address_length: value-result argument
        sockaddr_in client_address;
        socklen_t address_length = sizeof(sockaddr_in);

        poll(this->wait_set, this->wait_set_size, -1);

        int connection = -1;

        for (int i = 0; i < this->wait_set_size; i++) {
            if (this->wait_set[i].revents == POLLIN) {
                if (this->wait_set[i].fd == this->receive_socket) {
                    connection = accept_request((sockaddr*) &client_address, &address_length);
                } else {
                    connection = this->wait_set[i].fd;
                }

                if (connection != -1) {
                    request_handler(&client_address, connection);
                }
            }
            if (this->wait_set[i].revents & (POLLERR | POLLHUP | POLLNVAL)) {
                close_request(this->wait_set[i].fd);
            }
        }
    }
}

void StreamServer::bind_server()
{
    bind(this->receive_socket, (sockaddr*) server_address, sizeof(sockaddr_in));
}

void StreamServer::activate_server()
{
    listen(this->receive_socket, BACKLOG);
}

int StreamServer::accept_request(sockaddr* client_address, socklen_t* address_length)
{
    int socket = -1;

    if (wait_set_size < MAXIMUM_SOCKETS) {
        socket = accept(this->receive_socket, client_address, address_length);

        add_wait_set(socket);
    }

    return socket;
}

void StreamServer::close_request(int socket)
{
    remove_wait_set(socket);

    close(socket);
}