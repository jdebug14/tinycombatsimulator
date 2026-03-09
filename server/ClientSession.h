#pragma once
#include <string>
#include <netinet/in.h>

class ClientSession {
public:
    ClientSession(int clientfd, sockaddr_in clientAddr);
    ~ClientSession();

    void run();

private:
    int clientfd_;
    sockaddr_in clientAddr_;
    enum class ReceiveResult {
        Message,
        Disconnect,
        Error
    };

    ReceiveResult receiveMessage(std::string& out);
};