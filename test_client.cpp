#include <iostream>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);

    sockaddr_in server{};
    server.sin_family = AF_INET;
    server.sin_port = htons(5000);

    inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

    if (connect(sock, (sockaddr*)&server, sizeof(server)) < 0) {
        std::cerr << "Connection failed\n";
        return 1;
    }
    std::cout << "Connected to server\n";

    const char* message = "PING";
    send(sock, message, strlen(message), 0);

    char buffer[1024] = {0};
    recv(sock, buffer, sizeof(buffer), 0);
    std::cout << "Received: " << buffer << std::endl;

    close(sock);

    return 0;
}