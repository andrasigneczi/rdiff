#ifndef __LOGGERINTERFACE_H__
#define __LOGGERINTERFACE_H__

#include <string>
#include <memory>

class LoggerInterface;
using LoggerInterfaceUPtr = std::unique_ptr<LoggerInterface>;

class LoggerInterface {
public:
    virtual ~LoggerInterface() = default;
    virtual void log(std::string_view fileName, int line, std::string_view className, std::string_view functionName, std::string_view message) noexcept = 0;

    static void log(LoggerInterfaceUPtr& l, std::string_view fileName, int line, std::string_view className, std::string_view functionName, std::string_view message) noexcept {
        if(l) l->log(std::move(fileName), line, std::move(className), std::move(functionName), std::move(message));
    }
};


#endif // __LOGGERINTERFACE_H__
