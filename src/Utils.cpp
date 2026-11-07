#include "Utils.h"
#include <iostream>

#include <cctype>

namespace utils {

std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t\r\n");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t\r\n");
    return s.substr(start, end - start + 1);
}

std::string toLower(const std::string& s) {
    std::string out = s;
    for (size_t i = 0; i < out.length(); i++) {
        out[i] = (char)std::tolower((unsigned char)out[i]);
    }
    return out;
}

std::string toUpper(const std::string& s) {
    std::string out = s;
    for (size_t i = 0; i < out.length(); i++) {
        out[i] = (char)std::toupper((unsigned char)out[i]);
    }
    return out;
}

bool equalsIgnoreCase(const std::string& a, const std::string& b) {
    return toLower(a) == toLower(b);
}

std::vector<std::string> splitFields(const std::string& line) {
    std::vector<std::string> fields;
    size_t start = 0;
    size_t end = line.find('|');
    
    while (end != std::string::npos) {
        fields.push_back(trim(line.substr(start, end - start)));
        start = end + 1;
        end = line.find('|', start);
    }
    fields.push_back(trim(line.substr(start)));
    return fields;
}

bool isBlankOrComment(const std::string& line) {
    std::string trimmed = trim(line);
    return trimmed.empty() || trimmed[0] == '#';
}

bool readLine(const std::string& prompt, std::string& out) {
    std::cout << prompt;
    if (!std::getline(std::cin, out)) return false;
    out = trim(out);
    return true;
}

bool parseInt(const std::string& s, int& out) {
    if (s.empty()) return false;
    for (size_t i = 0; i < s.length(); i++) {
        if (!std::isdigit((unsigned char)s[i])) return false;
    }
    try {
        out = std::stoi(s);
        return true;
    } catch (...) {
        return false;
    }
}

} // namespace utils
