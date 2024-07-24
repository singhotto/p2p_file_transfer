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
#include "ThreadPool.hh"

class Server
{
private:
    /* data */
    struct sockaddr_in address;
    int server_fd;
    int opt;
    int addrlen;
    int PORT;
    ThreadPool t_pool;
    std::vector<int> clients;

public:
    Server(int port);
    ~Server();

    void start();
};

#endif