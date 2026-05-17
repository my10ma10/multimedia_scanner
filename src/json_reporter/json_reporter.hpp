#pragma once

#include <filesystem>
#include <unordered_map>
#include <thread>
#include <nlohmann/json.hpp>
#include "http_server/http_server.hpp"

namespace fs = std::filesystem;

class JsonReporter {
private:
    HttpServer server_;

    std::thread server_thread_;
    fs::path report_file_;

    nlohmann::json json_data_;

    std::unordered_map<std::string, std::string> extensions_;

public:
    JsonReporter();
    ~JsonReporter();

    void saveReport(const fs::path& path);

    void clearJsonData();

    bool isValidExtension(const std::string& ext) const;

private:
    bool isAudio(const fs::path& file_extension) const;
    bool isVideo(const fs::path& file_extension) const;
    bool isImage(const fs::path& file_extension) const;

    bool isMediaType(const fs::path& file_extension, const std::string& mediatype) const;
    
    void validateExtensionSet(
        const std::string& filepath = "multimedia_extensions.json"
    );
};