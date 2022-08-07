#include <vector>
#include <string>
#include <iostream>
#include <sys/socket.h>
#include <unistd.h>
#include "file.hpp"
#include "flower.hpp"
#include "sock.hpp"

#define SERVER_PORT 1234

int main(int argc, char** argv) {
    const int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock < 0) {
        perror("error creating socket");
    }
    sock::bindSocketToPort(sock, SERVER_PORT);
    int client_sock = sock::acceptClient(sock);

    char buffer[4096];
    int read_bytes = recv(client_sock, buffer, sizeof(buffer), 0);
    if (read_bytes == 0) {
        exit(0);
    }
    else if (read_bytes < 0) {
        perror("error");
    }
    else {
        std::cout<<buffer<<"\n";
    }
    char message[] = "success";
    int sent_bytes = send(client_sock, message, read_bytes, 0);
    if (sent_bytes < 0) {
        perror("error sending to client");
    }
    close(sock);
    return 0;
}