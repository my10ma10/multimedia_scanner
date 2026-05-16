#include "json_reporter.hpp"
#include <fstream>
#include <thread>
#include <unistd.h>
#include <pwd.h>

JsonReporter::JsonReporter() : server_(json_data_) {
    report_file_ = getpwuid(getuid())->pw_dir;
    extensions_ = readExtensions();
    
    std::thread server_thread([this]() {
        server_.start();
    });

    server_thread.join();
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
    if (!extensions_.contains(mediatype) && extensions_[mediatype].is_array()) {
        throw std::runtime_error(mediatype + " not found in extensions json");
    }
    for (const auto& media_ext : extensions_[mediatype]) {
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
