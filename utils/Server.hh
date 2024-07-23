#ifndef SERVER__GUARD
#define SERVER__GUARD

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

class Server
{
private:
    /* data */
    struct sockaddr_in address;
    int server_fd, new_socket;
    int opt;
    int addrlen;
    int PORT;

public:
    Server(int port);
    ~Server();

    void start();
};

#endif