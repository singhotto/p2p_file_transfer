#include "Server.hh"

Server::Server(int port) : PORT(port) {
    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set socket options
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    addrlen = sizeof(address);

    // Bind the socket to the address and port
    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is listening on port " << PORT << std::endl;

    t_pool.Start();
}

Server::~Server() {
    for(int& id : clients){
        close(id);
    }
    close(server_fd);
}

// Function to handle each client connection
void handle_client(int client_socket, std::vector<int>& clients) {
    std::cout << "Connection established with client " << client_socket << std::endl;

    // Specify the file to send
    // const char *filename = "./test.cpp";  // Change to your file name

    // send_file(client_socket, filename);
    long i = 0;
    while (i < 9999999999L){
        i++;
    }

    std::cout << "Closing connection with client " << client_socket << std::endl;
    close(client_socket);
    clients.erase(std::remove(clients.begin(), clients.end(), client_socket), clients.end());
}

void Server::start() {
    while (true) {
        int client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen);
        
        if (client_socket < 0) {
            perror("accept failed");
            continue;
        }

        clients.push_back(client_socket);

        // Capture clients correctly in the lambda
        t_pool.QueueJob([this, client_socket]() { handle_client(client_socket, clients); });
    }
}