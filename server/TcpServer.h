#include <string>

class TcpServer {
public:
    TcpServer(int port);
    ~TcpServer();

    void run();
private:
    int serverfd_;
    enum class ReceiveResult {
        Message,
        Disconnect,
        Error
    };

    void handleClient(int clientfd); 
    static ReceiveResult receiveMessage(int clientfd, std::string& out);
};