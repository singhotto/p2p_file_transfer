#include <iostream>
#include "./utils/Server.hh"
#include "./utils/FileManager.hh"

void printBinaryDataAsASCII(const std::vector<char>& data) {
    for (char c : data) {
        if (std::isprint(static_cast<unsigned char>(c))) {
            std::cout << c;
        } else {
            std::cout << '\n';
        }
    }
    std::cout << '\n';
}

int main(){
    Server server(8080);
    server.start();
    return 0;
}