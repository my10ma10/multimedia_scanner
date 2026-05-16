#pragma once

#include <nlohmann/json.hpp>
#include "socket/socket.hpp"

class HttpServer {
private:
    Socket socket_;
    int port_;

    nlohmann::json& json_data_;

public:
    HttpServer(nlohmann::json& j, int port = 1234);
    ~HttpServer();

    HttpServer(const HttpServer&) = delete;
    HttpServer& operator=(const HttpServer&) = delete;

    HttpServer(HttpServer&&) = delete;
    HttpServer& operator=(HttpServer&&) = delete;

    void start();

    void close();

private:
    std::string createResponse();
};
