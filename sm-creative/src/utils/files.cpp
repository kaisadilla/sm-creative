#include "utils/files.h"

namespace utils {
    std::string readTextFile (const char* filePath) {
        std::string file_content = "";

        std::ifstream file(filePath);
        if (file.is_open()) {
            std::string line;

            while (std::getline(file, line)) {
                file_content += line + "\n";
            }

            file.close();
        }
        else {
            std::cerr << "Couldn't access json file: " << filePath << "\n";
        }

        return file_content;
    }

    std::vector<unsigned char> readBinaryFile (const std::string& filePath) {
        std::ifstream in(filePath, std::ios::in | std::ios::binary);
        std::vector<unsigned char> data((std::istreambuf_iterator<char>(in)), std::istreambuf_iterator<char>());
        return data;
    }
}