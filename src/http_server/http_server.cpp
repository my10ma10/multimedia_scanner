#include "http_server.hpp"
#include <iostream>
#include <thread>
#include <chrono>

using namespace std::chrono_literals;

HttpServer::HttpServer(nlohmann::json& j, int port) 
    : json_data_(j), port_(port)
{
}

HttpServer::~HttpServer() {
    HttpServer::close();
}

void HttpServer::start() {
    if (!socket_.bind(std::to_string(port_))) {
        return;
    }
    if (!socket_.listen(10)) {
        return;
    }

    while (true) {
        auto client_socket = socket_.accept();
        if (!client_socket) {
            continue;
        }

        std::thread http_client_thread([sock = std::move(*client_socket), this]() mutable {
            auto request = sock.recv_http_header();
            if (!request) {
                return;
            }
            if (request->find("GET /media_files") != std::string::npos) {
                auto response = createResponse();
                sock.send(response);
            }
        });
        
        http_client_thread.detach();

    }

}

void HttpServer::close() {
    socket_.close();
}

std::string HttpServer::createResponse() {
    std::string body = json_data_.dump(4);
    std::string response = 
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: application/json\r\n"
            "Content-Length: " + std::to_string(body.size()) + "\r\n"
            "Connection: close\r\n"
            "\r\n"
            + body;
    return response;
}
