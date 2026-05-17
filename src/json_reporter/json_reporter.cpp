#include "json_reporter.hpp"
#include <fstream>
#include <iostream>
#include <thread>
#include <unistd.h>
#include <pwd.h>

JsonReporter::JsonReporter() : server_(json_data_) {
    report_file_ = getpwuid(getuid())->pw_dir;
    extensions_json_ = readExtensions();
    validateExtensionSet();
    
    std::thread server_thread([this]() {
        server_.start();
    });

    server_thread.detach();
}

void JsonReporter::saveReport(const fs::path& path) {
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
    return extensions_set_.count(ext) > 0;
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
    if (!extensions_json_.contains(mediatype) && extensions_json_[mediatype].is_array()) {
        throw std::runtime_error(mediatype + " not found in extensions json");
    }
    for (const auto& media_ext : extensions_json_[mediatype]) {
        if (file_extension.string() == media_ext.get<std::string>()) {
            return true;
        }
    }
    return false;
}


nlohmann::json JsonReporter::readExtensions(const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open file: " + filepath);
    }
    
    return nlohmann::json::parse(file);
}

void JsonReporter::validateExtensionSet() {
    extensions_set_.clear();
    for (const auto& [media_category, ext_list] : extensions_json_.items()) {
        for (const auto& ext : ext_list) {
            extensions_set_.insert(ext.get<std::string>());
        }
    }
}
