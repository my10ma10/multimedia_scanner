#pragma once

#include "iterator/iterator.hpp"

class Scanner {
private:
    Iterator iterator_;


    int sec_period_;

public:
    Scanner(int sec_period, const std::string& dir_path);

    void scan();
};