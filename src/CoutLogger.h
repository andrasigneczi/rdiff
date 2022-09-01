#ifndef __COUTLOGGER_H__
#define __COUTLOGGER_H__

#include "LoggerInterface.h"

class CoutLogger final : public LoggerInterface {
    friend class RdiffBuilder;
public:
    enum class Type {
        VERBOSE,
        DEBUG
    };
    void log(std::string_view fileName, int line, std::string_view className, std::string_view functionName, std::string_view message) noexcept override;

private:
    CoutLogger(Type type) : type_(type){}
    Type type_;
};

#endif // __COUTLOGGER_H__
