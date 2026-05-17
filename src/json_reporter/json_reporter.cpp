#include "json_reporter.hpp"
#include <fstream>
#include <unistd.h>
#include <pwd.h>

JsonReporter::JsonReporter() : server_(json_data_, json_mutex_) {
    report_file_ = getpwuid(getuid())->pw_dir;
    validateExtensionSet();
    
    server_thread_ = std::thread([this]() {
        server_.start();
    });
}

JsonReporter::~JsonReporter() {
    server_.stop();
    if (server_thread_.joinable()) {
        server_thread_.join();
    }
}

void JsonReporter::saveReport(const fs::path& path) {
    std::scoped_lock lock(json_mutex_);
    if (isAudio(path.extension())) {
        json_data_["audio"].push_back(path);
    }
    else if (isVideo(path.extension())) {
        json_data_["video"].push_back(path);
    }
    else if (isImage(path.extension())) {
        json_data_["images"].push_back(path);
    }
    else {
        throw std::runtime_error(path.string() + "cannot be saved in json data");
    }
}

void JsonReporter::clearJsonData() {
    json_data_.clear();
}

bool JsonReporter::isValidExtension(const std::string& ext) const {
    return extensions_.count(ext) > 0;
}

bool JsonReporter::isAudio(const fs::path& file_extension) const {
    return isMediaType(file_extension, "audio");
}

bool JsonReporter::isVideo(const fs::path& file_extension) const {
    return isMediaType(file_extension, "video");
}

bool JsonReporter::isImage(const fs::path& file_extension) const {
    return isMediaType(file_extension, "images");
}


bool JsonReporter::isMediaType(const fs::path& file_extension, const std::string& mediatype) const {
    auto it = extensions_.find(file_extension.string());
    if (it == extensions_.end()) {
        throw std::runtime_error(mediatype + " not found in extensions json");
    }
    
    return mediatype == it->second;
}

void JsonReporter::validateExtensionSet(
    const std::string& filepath
) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filepath);
    }
    
    nlohmann::json ext_json = nlohmann::json::parse(file);
    
    extensions_.clear();
    for (const auto& [media_category, ext_list] : ext_json.items()) {
        for (const auto& ext : ext_list) {
            extensions_[ext.get<std::string>()] = media_category;
        }
    }
}
