#include "TcpServer.h"
#include "RequestHandler.h"
#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <sys/socket.h>
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

    sockaddr_in client_address{};
    socklen_t client_len = sizeof(client_address);
    int client_fd = accept(serverfd_, (sockaddr*)&client_address, &client_len);

    while (true) {
        std::string clientMessage;
        ReceiveResult result = TcpServer::receiveMessage(client_fd, clientMessage);
        if (result == ReceiveResult::Disconnect) {
            std::cout << "Client disconnected\n";
            break;
        } else if (result == ReceiveResult::Error) {
            std::cerr << "Receive failed\n";
            break;
        }
        std::cout << "Received: " << clientMessage << std::endl;
        RequestType rqst = parseRequest(clientMessage);
        std::string reply = handleRequest(rqst);
        send(client_fd, reply.c_str(), reply.size(), 0);
    }
}

TcpServer::ReceiveResult TcpServer::receiveMessage(int clientfd, std::string& out) {
    char buffer[1024] = {0};
    int bytesReceived = recv(clientfd, buffer, sizeof(buffer), 0);
    if (bytesReceived == 0) {
        return ReceiveResult::Disconnect;
    } else if (bytesReceived < 0) {
        return ReceiveResult::Error;
    }
    out.assign(buffer, bytesReceived);
    return ReceiveResult::Message;
}