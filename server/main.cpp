#include "TcpServer.h"

int main() {
    TcpServer server(5000);
    server.run();
    return 0;
}