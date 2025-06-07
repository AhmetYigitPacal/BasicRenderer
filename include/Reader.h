#ifndef READER_H_
#define READER_H_

#include <vector>
#include <string>
#include <fstream>
#include <sstream>

class Reader {
public:
    static std::string readFileAsString(const std::string& filePath) {
        std::ifstream file(filePath);
        
        if(!file) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
        }

        return std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    }

    static std::vector<std::string> readFileAsLines(const std::string& filePath) {
        std::ifstream file(filePath);
        if (!file) {
            std::cerr << "Failed to open file: " << filePath << std::endl;
        }

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line)) {
            lines.push_back(line);
        }

        return lines;
    }

    static std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;

        while (std::getline(ss, token, delimiter)) {
            tokens.push_back(token);
        }

        return tokens;
    }

};

#endif // READER_H_