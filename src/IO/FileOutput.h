#ifndef __FILEOUTPUT_H__
#define __FILEOUTPUT_H__

#include "OutputInterface.h"
#include <string>
#include <fstream>

class FileOutput : public OutputInterface {
public:
    FileOutput(std::string fileName) noexcept;
    void put(int8_t c) override;
    void put(int32_t c) override;
    void put(int64_t c) override;

    void put(uint8_t c) override;
    void put(uint32_t c) override;
    void put(uint64_t c) override;

    void put(const std::vector<uint8_t>& buffer, size_t length) override;

    [[nodiscard]] bool open() override;
    void close() override;
    void flush() override;

private:
    std::string fileName_;
    std::ofstream file_;
};

#endif // __FILEOUTPUT_H__
