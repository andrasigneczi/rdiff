#include "CoutLogger.h"
#include <iostream>

void CoutLogger::log(std::string_view  fileName, int line, std::string_view className, std::string_view functionName, std::string_view message) noexcept {
    if(type_ == Type::DEBUG) {
        if(auto pos = fileName.rfind('/'); pos != std::string_view::npos) {
            fileName = fileName.substr(pos + 1);
        }
        std::cout << fileName << "(" << line << ") " << className << "::" << functionName << ": " << message;
    } else {
        std::cout << message;
    }
}
