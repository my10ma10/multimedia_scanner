#include "http_server.hpp"
#include <iostream>

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

        auto request = client_socket->recv_http_header();
        if (!request) {
            std::cerr << "Received empty request\n";
            return;
        }

        std::cout << "get request\n";
        if (request->find("GET /media_files") != std::string::npos) {
            client_socket->send(createResponse());
        }
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
            + body;
    return response;
}
