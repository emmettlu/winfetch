#pragma once

#include <chrono>
#include <string>

// System information functions
std::wstring getusername();
std::wstring gethostname();
std::chrono::milliseconds getuptime();

// int get_package_count();
