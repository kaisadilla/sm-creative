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
}