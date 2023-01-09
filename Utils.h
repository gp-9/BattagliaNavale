#ifndef UTILS_H_
#define UTILS_H_
#include <string>
#include <vector>

namespace Utils {
    static const std::string SPACES = " \t\r\n\v\f";

    std::string trim(const std::string& input);
    std::vector<std::string> split(const std::string& input, const std::string& separator);
}

#endif // UTILS_H_
