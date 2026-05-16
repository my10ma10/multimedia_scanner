#pragma once

#include <filesystem>
#include <vector>

inline std::vector<std::string> file_extencions = {".mp3", ".wav", ".mp4", ".jpg", ".png"};

namespace fs = std::filesystem;

class Iterator {
private:
    // JsonReporter reporter_;

    fs::path dir_path_;

public:
    Iterator(const std::string& dir_path = "~");

    void iterate();
};