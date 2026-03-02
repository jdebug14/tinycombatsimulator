#include <iostream>
#include <cstring>
#include <string>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

enum ReceiveResult {
    Message,
    Disconnect,
    Error
};

ReceiveResult receiveMessage(int fd, std::string& out) {
    char buffer[1024] = {0};
    int bytesReceived = recv(fd, buffer, sizeof(buffer), 0);
    if (bytesReceived == 0) {
        return ReceiveResult::Disconnect;
    } else if (bytesReceived < 0) {
        return ReceiveResult::Error;
    }
    out.assign(buffer, bytesReceived);
    return ReceiveResult::Message;
}

std::string handleCommand(const std::string& message) {
    if (message == "PING") {
        return "PONG";
    } else if (message == "PLAYER_STATUS") {
        return "ALIVE";
    } else {
        return "UNKNOWN COMMAND";
    }
}

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0) {
        std::cerr << "Failed to create socket\n";
        return 1;
    }

    sockaddr_in address{};
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(5000);

    // Allow the port to be reused immediately
    int opt = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed\n";
        return 1;
    }

    if (listen(server_fd, 1) < 0) {
        std::cerr << "Listen failed\n";
        return 1;
    }
    std::cout << "Server listening...\n";

    sockaddr_in client_address{};
    socklen_t client_len = sizeof(client_address);

    int client_fd = accept(server_fd, (sockaddr*)&client_address, &client_len);
    if (client_fd < 0) {
        std::cerr << "Accept failed\n";
        return 1;
    }

    while (true) {
        std::string clientMessage;
        ReceiveResult result = receiveMessage(client_fd, clientMessage);
        if (result == ReceiveResult::Disconnect) {
            std::cout << "Client disconnected\n";
            break;
        } else if (result == ReceiveResult::Error) {
            std::cerr << "Receive failed\n";
            break;
        }
        std::cout << "Received: " << clientMessage << std::endl;
        std::string reply = handleCommand(clientMessage);
        send(client_fd, reply.c_str(), reply.size(), 0);
    }

    close(client_fd);
    close(server_fd);
    
    return 0;
}