#pragma once
#include <atomic>

inline constexpr int BUF_SIZE = 4096;
inline std::atomic<bool> g_running{true};