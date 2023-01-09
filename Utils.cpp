#include "../../include/Utils/Utils.h"

std::string ltrim(const std::string& input) {
    std::size_t first = input.find_first_not_of(Utils::SPACES);
    if(first == std::string::npos) return "";
    return input.substr(first);
}

std::string rtrim(const std::string& input) {
    std::size_t last = input.find_last_not_of(Utils::SPACES);
    if(last == std::string::npos) return "";
    return input.substr(0, last + 1);
}

std::string Utils::trim(const std::string& input) {
    return ltrim(rtrim(input));
}

std::vector<std::string> Utils::split(const std::string& input, const std::string& separator) {
    std::size_t pos = 0;
    std::size_t oldpos = 0;
    std::vector<std::string> tokens;
    while(pos != std::string::npos) {
        pos = input.find(separator, oldpos);
        int len = pos - oldpos;
        tokens.push_back(input.substr(oldpos, len));
        oldpos = pos + separator.size();
    }
    return tokens;
}
