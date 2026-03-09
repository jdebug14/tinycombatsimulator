#include "ClientSession.h"
#include "RequestHandler.h"
#include <cstring>
#include <iostream>
#include <unistd.h>
#include <arpa/inet.h>

ClientSession::ClientSession(int clientfd, sockaddr_in clientAddr) 
    : clientfd_(clientfd), clientAddr_(clientAddr) {
        char ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &clientAddr_.sin_addr, ip, sizeof(ip));
        std::cout << "Client connected: " << ip << "\n";
}

ClientSession::~ClientSession() {
    close(clientfd_);
    std::cout << "Client session closed\n";
}

void ClientSession::run() {
    while (true) {
        std::string clientMessage;
        ReceiveResult result = receiveMessage(clientMessage);
        if (result == ReceiveResult::Disconnect) {
            std::cout << "Client disconnected\n";
            break;
        } else if (result == ReceiveResult::Error) {
            std::cerr << "Receive failed\n";
            break;
        }
        std::cout << "Received: " << clientMessage << "\n";
        RequestType rqst = parseRequest(clientMessage);
        std::string reply = handleRequest(rqst);
        send(clientfd_, reply.c_str(), reply.size(), 0);
    }
}

ClientSession::ReceiveResult ClientSession::receiveMessage(std::string& out) {
    char buffer[1024] = {0};
    int bytesReceived = recv(clientfd_, buffer, sizeof(buffer), 0);
    if (bytesReceived == 0) {
        return ReceiveResult::Disconnect;
    } else if (bytesReceived < 0) {
        return ReceiveResult::Error;
    }
    out.assign(buffer, bytesReceived);
    return ReceiveResult::Message;
}