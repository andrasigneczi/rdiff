#include "ClockReal.h"
#include <iostream>

void ClockReal::markTime() {
    nows_.push_back(std::chrono::high_resolution_clock::now());
}

void ClockReal::printResult() {
    std::cout << "------" << title_ << "------\n";

    for(size_t i = nows_.size() - 1; i > 0; --i) {
        double duration = std::chrono::duration<double>(nows_[i] - nows_[i - 1]).count();
        std::cout << "Time t" << i << "-t" << i - 1 << ": " << duration << " s ";
        if(duration > 1.) std::cout << "!!!!!!!!!!!!!";
        std::cout << "\n";
    }
    std::cout << "------End------\n\n";
}

void ClockReal::reset() {
    nows_.clear();
    duration_ = 0.;
}

void ClockReal::start() {
    startTime_ = std::chrono::high_resolution_clock::now();
}

void ClockReal::stop() {
    auto stop = std::chrono::high_resolution_clock::now();
    duration_ += std::chrono::duration<double>(stop - startTime_).count();
}

void ClockReal::printDuration() {
    std::cout << "------" << title_ << "------\n";
    std::cout << "Duration: " << duration_ << " s";
    if(duration_ > 1.) std::cout << "!!!!!!!!!!!!!";
    std::cout << "\n";
    std::cout << "------End------\n\n";
}
