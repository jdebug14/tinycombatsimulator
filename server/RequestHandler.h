#pragma once
#include "../shared/Protocol.h"
#include <string>

RequestType parseRequest(const std::string& message);
std::string handleRequest(RequestType rqst);