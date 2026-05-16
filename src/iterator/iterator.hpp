#pragma once

#include <filesystem>
#include <vector>

#include "json_reporter/json_reporter.hpp"

namespace fs = std::filesystem;

class Iterator {
private:
    JsonReporter reporter_;
    fs::path dir_path_;

public:
    Iterator(const std::string& dir_path = "~");

    void iterate();
};