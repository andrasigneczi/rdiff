#include "FileInput.h"
#include <iostream>

FileInput::FileInput(std::string fileName) noexcept
: fileName_(std::move(fileName)) {

}

bool FileInput::get(uint8_t& c) {
    file_.read((char*)&c, sizeof(c));
    return file_.gcount() == sizeof(c);
}

bool FileInput::get(uint32_t& c) {
    file_.read((char*)&c, sizeof(c));
    return file_.gcount() == sizeof(c);
}

bool FileInput::get(uint64_t& c) {
    file_.read((char*)&c, sizeof(c));
    return file_.gcount() == sizeof(c);
}

bool FileInput::get(int32_t& c) {
    file_.read((char*)&c, sizeof(c));
    return file_.gcount() == sizeof(c);
}

bool FileInput::get(int64_t& c) {
    file_.read((char*)&c, sizeof(c));
    return file_.gcount() == sizeof(c);
}

bool FileInput::get(std::vector<uint8_t>& buffer, size_t length) {
    if(buffer.size() < length) buffer.resize(length);
    file_.read((char*)buffer.data(), (long)length);
    return file_.gcount() == (long)length;
}

bool FileInput::open() {
    file_.open(fileName_, std::ios::in | std::ios::binary);
    if(!file_.is_open()) return false;
    return true;
}

void FileInput::close() {
    file_.close();
}

bool FileInput::eof() {
    return file_.eof();
}

long FileInput::size() {
    if(file_.is_open()) {
        auto state = file_.rdstate();   // get state
        state &= ~std::ios_base::failbit;  // remove failbit from it
        state &= ~std::ios_base::eofbit;  // remove failbit from it
        file_.clear(state);             // clear old state and set new state

        auto originalPosition = file_.tellg();
        //std::cout << "FileInput::size originalPosition: " << originalPosition << "\n";
        file_.seekg(0, file_.end);
        auto size = file_.tellg();
        //std::cout << "FileInput::size: " << size << "\n";
        file_.seekg(originalPosition, file_.beg);
        return size;
    }
    return 0;
}

void FileInput::seek(long pos) {
    if(file_.is_open()) {
        file_.seekg(pos, file_.beg);
    }
}
