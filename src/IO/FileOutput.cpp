#include "FileOutput.h"

FileOutput::FileOutput(std::string fileName) noexcept
: fileName_(std::move(fileName)) {

}

void FileOutput::put(int8_t c) {
    file_.write((const char*)&c, sizeof(c));
}

void FileOutput::put(int32_t c) {
    file_.write((const char*)&c, sizeof(c));
}

void FileOutput::put(int64_t c) {
    file_.write((const char*)&c, sizeof(c));
}

void FileOutput::put(uint8_t c) {
    file_.write((const char*)&c, sizeof(c));
}

void FileOutput::put(uint32_t c) {
    file_.write((const char*)&c, sizeof(c));
}

void FileOutput::put(uint64_t c) {
    file_.write((const char*)&c, sizeof(c));
}

void FileOutput::put(const std::vector<uint8_t>& buffer, size_t length) {
    file_.write((const char*)buffer.data(), (long)length);
}

bool FileOutput::open() {
    file_.open(fileName_, std::ios::out | std::ios::trunc | std::ios::binary);
    if(!file_.is_open()) return false;
    return true;
}

void FileOutput::close() {
    file_.close();
}

void FileOutput::flush() {
    file_.flush();
}
