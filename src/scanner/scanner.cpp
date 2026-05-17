#include "scanner.hpp"
#include <chrono>
#include <thread>
#include <iostream>

namespace ch = std::chrono;


Scanner::Scanner(int sec_period, const std::string& dir_path) 
    : iterator_(dir_path), sec_period_(sec_period)
{
}

void Scanner::scan() {
    auto start_time = ch::steady_clock::now();

    while (g_running) {
        start_time = ch::steady_clock::now();
        iterator_.iterate();
        
        std::cout << "Waiting for " << sec_period_ << " seconds...\n";
        // std::this_thread::sleep_until(start_time + ch::seconds(sec_period_));
        auto wake_time = ch::steady_clock::now() + ch::seconds(sec_period_);
        while (g_running && ch::steady_clock::now() < wake_time) {
            std::this_thread::sleep_for(ch::milliseconds(100));
        }
    }
}
