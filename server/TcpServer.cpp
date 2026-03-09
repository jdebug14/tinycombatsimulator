#include "TcpServer.h"
#include "ClientSession.h"
#include <iostream>
#include <unistd.h>

TcpServer::TcpServer(int port) {
    serverfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (serverfd_ < 0) {
        throw std::runtime_error("Failed to create socket");
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    // Allow the port to be reused immediately
    int opt = 1;
    setsockopt(serverfd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(serverfd_, (sockaddr*)&address, sizeof(address)) < 0) {
        throw std::runtime_error("Failed to bind socket");
    }
}

TcpServer::~TcpServer() {
    close(serverfd_);
    std::cout << "Server closed\n";
}

void TcpServer::run() {
    if (listen(serverfd_, 1) < 0) {
        throw std::runtime_error("Listen failed");
    }
    std::cout << "Server listening...\n";

    while (true) {
        sockaddr_in clientAddr{};
        socklen_t clientLen = sizeof(clientAddr);
        int clientfd = accept(serverfd_, (sockaddr*)&clientAddr, &clientLen);
        if (clientfd < 0) {
            std::cerr << "Client accept failed\n";
            continue;
        }
        ClientSession clientSession(clientfd, clientAddr);
        clientSession.run();
    }
}