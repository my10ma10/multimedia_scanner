#pragma once

#include <nlohmann/json.hpp>
#include "socket/socket.hpp"
#include <thread>
#include <mutex>
#include <memory>

class HttpServer {
private:
    std::unique_ptr<Socket> listen_socket_ = nullptr;
    int port_;

    nlohmann::json& json_data_;
    std::mutex& json_mutex_;

public:
    HttpServer(nlohmann::json& j, std::mutex& mtx, int port = 1234);
    ~HttpServer();

    HttpServer(const HttpServer&) = delete;
    HttpServer& operator=(const HttpServer&) = delete;

    HttpServer(HttpServer&&) = delete;
    HttpServer& operator=(HttpServer&&) = delete;

    void start();
    void stop();

    void close();

private:
    std::string createResponse();
};
