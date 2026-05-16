#pragma once

#include <filesystem>
#include <nlohmann/json.hpp>
#include "http_server/http_server.hpp"

namespace fs = std::filesystem;

class JsonReporter {
private:
    HttpServer server_;
    fs::path report_file_;

    nlohmann::json json_data_;
    nlohmann::json extensions_;

public:
    JsonReporter();

    void saveReport(const fs::path& path);

    void clearJsonData();

    nlohmann::json getExtensions() const { return extensions_; }

private:
    bool isAudio(const fs::path& file_extension) const;
    bool isVideo(const fs::path& file_extension) const;
    bool isImage(const fs::path& file_extension) const;

    bool isMediaType(const fs::path& file_extension, const std::string& mediatype) const;
    
    nlohmann::json readExtensions(
        const std::string& filepath = "multimedia_extensions.json"
    );
};