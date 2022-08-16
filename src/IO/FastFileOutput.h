#ifndef __FASTFILEOUTPUT_H__
#define __FASTFILEOUTPUT_H__

#include "OutputInterface.h"
#include <string>
#include <string.h>
#include <fstream>

class FastFileOutput : public OutputInterface {
public:
    FastFileOutput(std::string fileName) noexcept;
    void put(int8_t c) override;
    void put(int32_t c) override {putT(c);}
    void put(int64_t c) override {putT(c);}

    void put(uint8_t c) override;
    void put(uint32_t c) override {putT(c);}
    void put(uint64_t c) override {putT(c);}

    void put(const std::vector<uint8_t>& buffer, size_t length) override;

    [[nodiscard]]bool open() override;
    void close() override;
    void flush() override;

private:
    void flushBuffer();

    template<typename T> void putT(T& c);

    std::string fileName_;
    int fileNo_{-1};
    std::unique_ptr<uint8_t[]> buffer_;
    static constexpr size_t bufferSize_{16'000};
    size_t bufferPos_{};
};

template<typename T>
void FastFileOutput::putT(T& c) {
    if(bufferPos_ + sizeof(c) > bufferSize_) flushBuffer();
    memcpy(buffer_.get() + bufferPos_, &c, sizeof(c));
    //*(T*)(buffer_.get() + bufferPos_) = c;
    bufferPos_ += sizeof(c);
}

#endif // __FASTFILEOUTPUT_H__
