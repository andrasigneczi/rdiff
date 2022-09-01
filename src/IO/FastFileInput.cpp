#include "FastFileInput.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

FastFileInput::FastFileInput(std::string fileName) noexcept
: fileName_(std::move(fileName))
, buffer_(std::make_unique<uint8_t[]>(bufferSize_)){

}

bool FastFileInput::refillBuffer() noexcept {
    if(bufferPos_ == bufferContent_) {
        bufferContent_ = 0;
    } else {
        memmove(buffer_.get(), buffer_.get() + bufferPos_, bufferContent_ - bufferPos_);
        bufferContent_ -= bufferPos_;
    }
    bufferPos_ = 0;

    if(ssize_t retv = read(fileNo_, buffer_.get() + bufferContent_, bufferSize_ - bufferContent_); retv < 0) {
        return false;
    } else {
        bufferContent_ += (size_t)retv;
        eof_ = !retv;
    }
    return bufferContent_ > 0;
}

bool FastFileInput::open() {
    fileNo_ = ::open(fileName_.c_str(), O_RDONLY);
    return fileNo_ >= 0;
}

void FastFileInput::close() {
    ::close(fileNo_);
}

bool FastFileInput::eof() {
    return bufferPos_ == bufferContent_ && eof_;
}

long FastFileInput::size() {
    if(fileNo_ < 0) throw std::runtime_error("ERROR: FastFileInput::size: file is not open");
    if(fileSize_ == -1) {
        struct stat stat;
        if(fstat(fileNo_, &stat)) throw std::runtime_error("ERROR: FastFileInput::size: stat error");
        fileSize_ = stat.st_size;
    }
    return fileSize_;
}

void FastFileInput::seek(long pos) {
    if(long retv = lseek(fileNo_, pos, SEEK_SET); retv == -1) {
        throw std::runtime_error("ERROR: FastFileInput::seek");
    } else {
        bufferPos_ = 0;
        bufferContent_ = 0;
    }
}

bool FastFileInput::get(std::vector<uint8_t>& buffer, size_t length) {
    if(buffer.size() < length) buffer.resize(length);
    for(size_t copied = 0; copied != length;) {
        if(bufferPos_ + length - copied > bufferContent_ && !refillBuffer()) return false;
        if(bufferPos_ + length - copied > bufferContent_ && eof()) return false;
        if(bufferPos_ + length - copied > bufferContent_) {
            memcpy(buffer.data() + copied, buffer_.get() + bufferPos_, bufferContent_ - bufferPos_);
            copied += bufferContent_ - bufferPos_;
            bufferPos_ = bufferContent_;
        } else {
            memcpy(buffer.data() + copied, buffer_.get() + bufferPos_, length - copied);
            bufferPos_ += length - copied;
            copied = length;
        }
    }
    return true;
}
