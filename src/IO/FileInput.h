#ifndef __FILEINPUT_H__
#define __FILEINPUT_H__

#include "InputInterface.h"
#include <string>
#include <fstream>

class FileInput final : public InputInterface {
public:
    FileInput(std::string fileName) noexcept;

    [[nodiscard]] bool get(uint8_t& c) override;
    [[nodiscard]] bool get(uint32_t& c) override;
    [[nodiscard]] bool get(uint64_t& c) override;

    [[nodiscard]] bool get(int32_t& c) override;
    [[nodiscard]] bool get(int64_t& c) override;
    [[nodiscard]] bool get(std::vector<uint8_t>& buffer, size_t length) override;


    [[nodiscard]] bool open() override;
    void close() override;
    [[nodiscard]] bool eof() override;
    [[nodiscard]] long size() override;
    void seek(long pos) override;

private:
    template<typename T>
    [[nodiscard]] bool getT(T& c) {
        file_.read((char*)&c, sizeof(c));
        return file_.gcount() == sizeof(c);
    }

    std::string fileName_;
    std::ifstream file_;
};

#endif // __FILEINPUT_H__
