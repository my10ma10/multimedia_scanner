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

        for (const std::string& media_ext : file_extencions) {
            if (entry.path().extension() == media_ext) {
                std::cout << entry.path() << std::endl;
            }
        }
    }
    std::cout << "Iteration completed successfully\n";
}