#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace utils {
    std::string readTextFile(const char* filePath);
    std::vector<unsigned char> readBinaryFile(const std::string& filePath);
}