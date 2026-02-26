#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

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

    if (bind(server_fd, (sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "Bind failed\n";
        return 1;
    }

    if (listen(server_fd, 1) < 0) {
        std::cerr << "Listen failed\n";
        return 1;
    }

    std::cout << "Server listening on port 5000...\n";

    sockaddr_in client_address{};
    socklen_t client_len = sizeof(client_address);

    // Awaits a connection
    int client_fd = accept(server_fd, (sockaddr*)&client_address, &client_len);
    if (client_fd < 0) {
        std::cerr << "Accept failed\n";
        return 1;
    }

    std::cout << "Client connected\n";

    close(client_fd);
    close(server_fd);
    
    return 0;
}