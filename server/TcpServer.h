#pragma once

class TcpServer {
public:
    TcpServer(int port);
    ~TcpServer();

    void run();
private:
    int serverfd_;
};