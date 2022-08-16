#include "FastFileOutput.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <iostream>

FastFileOutput::FastFileOutput(std::string fileName) noexcept
: fileName_(std::move(fileName))
, buffer_(std::make_unique<uint8_t[]>(bufferSize_)){

}

void FastFileOutput::flushBuffer() {
    auto len = write(fileNo_, buffer_.get(), bufferPos_);
    if(len == -1) throw std::runtime_error("ERROR: FastFileOutput::flushBuffer write error");
    if((size_t)len == bufferPos_) {
        bufferPos_ = 0;
    } else {
        memmove(buffer_.get(), buffer_.get() + len, bufferPos_ - (size_t)len);
        bufferPos_ -= (size_t)len;
    }
}

void FastFileOutput::put(int8_t c) {
    if(bufferPos_ == bufferSize_) flushBuffer();
    buffer_[bufferPos_++] = (uint8_t)c;
}

void FastFileOutput::put(uint8_t c) {
    if(bufferPos_ == bufferSize_) flushBuffer();
    buffer_[bufferPos_++] = (uint8_t)c;
}

bool FastFileOutput::open() {
    fileNo_ = ::open(fileName_.c_str(), O_WRONLY|O_CREAT|O_TRUNC, S_IRWXU|S_IRWXG|S_IRWXO);
    if(fileNo_ < 0) return false;
    return true;
}

void FastFileOutput::close() {
    ::close(fileNo_);
}

void FastFileOutput::flush() {
    if(bufferPos_) flushBuffer();
}

void FastFileOutput::put(const std::vector<uint8_t>& buffer, size_t length) {
    for(size_t copied = 0; copied != length;) {
        if(bufferPos_ + length - copied > bufferSize_) {
            memcpy(buffer_.get() + bufferPos_, buffer.data() + copied, bufferSize_ - bufferPos_);
            copied += bufferSize_ - bufferPos_;
            bufferPos_ = bufferSize_;
            flushBuffer();
        } else {
            memcpy(buffer_.get() + bufferPos_, buffer.data() + copied, length - copied);
            bufferPos_ += length - copied;
            copied = length;
        }
    }
}
