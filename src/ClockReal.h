#ifndef __CLOCKREAL_H__
#define __CLOCKREAL_H__

#include "ClockInterface.h"
#include <chrono>
#include <vector>

class ClockReal final : public ClockInterface{
    friend class ClockFactory;
    ClockReal(std::string title) : title_(std::move(title)) {}

public:
    void markTime() override;
    void printResult() override;
    void reset() override;

    void start() override;
    void stop() override;
    void printDuration() override;

    ClockInterfaceUPtr clone() override {return ClockInterfaceUPtr(new ClockReal(*this));}
    void setTitle(std::string title) override {title_ = std::move(title);}

private:
    std::string title_;
    std::vector<std::chrono::time_point<std::chrono::high_resolution_clock>> nows_;
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime_;
    double duration_{};
};

#endif // __CLOCKREAL_H__
