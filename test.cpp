#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

void send_file(int socket, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        fwrite(buffer, 1, bytesRead, stdout);
        if (send(socket, buffer, bytesRead, 0) < 0) {
            perror("Failed to send file");
            break;
        }
    }
    fclose(file);
    printf("File sent successfully\n");
}

int main() {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);


    // Accept an incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t*)&addrlen)) < 0) {
        perror("accept");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connection established with client\n");

    // Specify the file to send
    const char *filename = "./test.cpp";  // Change to your file name

    send_file(new_socket, filename);

    printf("Closing connection\n");
    close(new_socket);
    close(server_fd);

    return 0;
}
