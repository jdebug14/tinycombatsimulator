#include "RequestHandler.h"

RequestType parseRequest(const std::string& message) {
    if (message == "PING") {
        return RequestType::Ping;
    } else if (message == "PLAYER_STATUS") {
        return RequestType::PlayerStatus;
    } else {
        return RequestType::Unknown;
    }
}

std::string handleRequest(RequestType rqst) {
    switch (rqst) {
    case RequestType::Ping:
        return "PONG";
    case RequestType::PlayerStatus:
        return "ALIVE";
    default:
        return "UNKNOWN COMMAND";
    }
}