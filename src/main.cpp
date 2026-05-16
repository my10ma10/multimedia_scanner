#include "scanner/scanner.hpp"

#include <iostream>
#include <string>

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Too few arguments\n";
        throw std::runtime_error("Expected period format in seconds and dir path");
    }
    try {
        int period = std::stoi(argv[1]);
        std::string dir_path = argv[2];

        Scanner scanner(period, dir_path);
        scanner.scan();
    }
    catch (const std::runtime_error& ex) {
        std::clog << "Runtime error: " << ex.what() << std::endl;
    }
    catch (const std::exception& ex) {
        std::clog << ex.what() << std::endl;
    }
    return 0;
}