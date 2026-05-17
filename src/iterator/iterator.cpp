#include "iterator.hpp"
#include <iostream>
#include <unistd.h>
#include <pwd.h>

Iterator::Iterator(const std::string& dir_path) {
    if (dir_path == "~") {
        dir_path_ = getpwuid(getuid())->pw_dir;
    }
    else {
        dir_path_ = dir_path;
    }
}

void Iterator::iterate() {
    std::cout << "Iterating media files...: \n";
    reporter_.clearJsonData();

    for (const auto& entry : fs::recursive_directory_iterator(dir_path_)) {
        if (!entry.is_regular_file()) {
            continue;
        }
        if (reporter_.isValidExtension(entry.path().extension().string())) {
            reporter_.saveReport(entry.path());
        }
            
    }
    std::cout << "Iteration completed successfully\n";
}