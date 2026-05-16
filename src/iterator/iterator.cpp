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
    dir_path_ /= "Dev/Personal";
}

void Iterator::iterate() {
    std::cout << "Iterating media files...: \n";
    for (const auto& entry : fs::recursive_directory_iterator(dir_path_)) {
        if (!entry.is_regular_file()) {
            continue;
        }

        for (const auto& media_list : reporter_.getExtensions()) {
            for (const std::string& media_ext : media_list) {
                if (entry.path().extension() == media_ext) {
                    // std::cout << entry.path() << std::endl;
                    reporter_.saveReport(entry.path());
                }
            }
        }
    }
    std::cout << "Iteration completed successfully\n";
}