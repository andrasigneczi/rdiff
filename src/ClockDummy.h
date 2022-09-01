#ifndef __CLOCKDUMMY_H__
#define __CLOCKDUMMY_H__

#include "ClockInterface.h"
#include <string>

class ClockDummy final : public ClockInterface {
    friend class ClockFactory;
    ClockDummy() = default;
public:
    void markTime() override {}
    void printResult() override {}
    void reset() override {}
    void start() override {}
    void stop() override {}
    void printDuration() override {}
    [[nodiscard]] ClockInterfaceUPtr clone() override {return nullptr;}
    void setTitle(std::string) override {}
};

#endif // __CLOCKDUMMY_H__
