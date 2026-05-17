#pragma once

#include <filesystem>
#include <unordered_set>
#include <nlohmann/json.hpp>
#include "http_server/http_server.hpp"

namespace fs = std::filesystem;

class JsonReporter {
private:
    HttpServer server_;
    fs::path report_file_;

    nlohmann::json json_data_;
    nlohmann::json extensions_json_;

    std::unordered_set<std::string> extensions_set_;

public:
    JsonReporter();

    void saveReport(const fs::path& path);

    void clearJsonData();

    bool isValidExtension(const std::string& ext) const;
    
private:
    bool isAudio(const fs::path& file_extension) const;
    bool isVideo(const fs::path& file_extension) const;
    bool isImage(const fs::path& file_extension) const;

    bool isMediaType(const fs::path& file_extension, const std::string& mediatype) const;
    
    nlohmann::json readExtensions(
        const std::string& filepath = "multimedia_extensions.json"
    );
    void validateExtensionSet();
};