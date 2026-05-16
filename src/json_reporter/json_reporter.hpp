#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>
#include "http_server/http_server.hpp"

namespace fs = std::filesystem;

class JsonReporter {
private:
    HttpServer server_;
    fs::path report_file_;

    nlohmann::json json_;

public:
    JsonReporter();

    void saveReport();
};