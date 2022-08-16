#ifndef __FASTFILEINPUT_H__
#define __FASTFILEINPUT_H__

#include "InputInterface.h"
#include <string>
#include <string.h>
#include <memory>

class FastFileInput final : public InputInterface {
public:
    FastFileInput(std::string fileName) noexcept;

    [[nodiscard]] bool get(uint8_t& c) override {return getT(c);}
    [[nodiscard]] bool get(uint32_t& c) override {return getT(c);}
    [[nodiscard]] bool get(uint64_t& c) override {return getT(c);}

    [[nodiscard]] bool get(int32_t& c) override {return getT(c);}
    [[nodiscard]] bool get(int64_t& c) override {return getT(c);}
    [[nodiscard]] bool get(std::vector<uint8_t>& buffer, size_t length) override;

    [[nodiscard]]bool open() override;
    void close() override;
    [[nodiscard]]bool eof() override;
    [[nodiscard]]long size() override;
    void seek(long pos) override;

private:
    bool refillBuffer() noexcept;

    template<typename T> bool getT(T& c);

    std::string fileName_;
    int fileNo_{-1};
    std::unique_ptr<uint8_t[]> buffer_;
    static constexpr size_t bufferSize_{16'000};
    size_t bufferPos_{};
    size_t bufferContent_{};
    long fileSize_{-1};
    bool eof_{};
};

template<typename T>
bool FastFileInput::getT(T& c) {
    if(bufferPos_ + sizeof(c) > bufferContent_ && !refillBuffer()) return false;
    if(bufferPos_ + sizeof(c) > bufferContent_ && eof_) return false;
    memcpy(&c, buffer_.get() + bufferPos_, sizeof(c));
    bufferPos_ += sizeof(c);
    return true;
}

#endif // __FASTFILEINPUT_H__
