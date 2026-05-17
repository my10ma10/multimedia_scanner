#include "http_server.hpp"
#include <iostream>
#include <chrono>

using namespace std::chrono_literals;

HttpServer::HttpServer(nlohmann::json& j, std::mutex& mtx, int port) 
    : json_data_(j), json_mutex_(mtx), port_(port)
{
}

HttpServer::~HttpServer() {
    HttpServer::close();
}

void HttpServer::start() {
    listen_socket_ = std::make_unique<Socket>();
    if (!listen_socket_->bind(std::to_string(port_))) {
        return;
    }
    if (!listen_socket_->listen(10)) {
        return;
    }

    while (g_running) {
        auto client_socket = listen_socket_->accept();
        if (!client_socket) {
            break;
        }

        std::thread([sock = std::move(*client_socket), this]() mutable {
            auto request = sock.recv_http_header();
            if (!request) {
                return;
            }
            if (request->find("GET /media_files") != std::string::npos) {
                auto response = createResponse();
                sock.send(response);
            }
        }).detach();
    }
}

void HttpServer::stop() {
    if (listen_socket_) {
        listen_socket_->close();
    }
}

void HttpServer::close() {
    if (listen_socket_) { 
        listen_socket_->close();
        listen_socket_.reset();
    }
}

std::string HttpServer::createResponse() {
    std::string body;
    {
        std::scoped_lock lock(json_mutex_);
        body = json_data_.dump(4);
    }
    std::string response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: " + std::to_string(body.size()) + "\r\n"
            "Connection: close\r\n"
            "\r\n"
            + body;
    return response;
}
