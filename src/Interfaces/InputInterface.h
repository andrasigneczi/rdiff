#ifndef __INPUTINTERFACE_H__
#define __INPUTINTERFACE_H__

#include <inttypes.h>
#include <memory>
#include <vector>

class FastFileInput;

class InputInterface {
public:
    virtual ~InputInterface() = default;

    [[nodiscard]] virtual bool get(uint8_t&) {throw std::runtime_error("InputInterface::get(uint8_t&) is not implemented");}
    [[nodiscard]] virtual bool get(uint16_t&) {throw std::runtime_error("InputInterface::get(uint16_t&) is not implemented");}
    [[nodiscard]] virtual bool get(uint32_t&) {throw std::runtime_error("InputInterface::get(uint32_t&) is not implemented");}
    [[nodiscard]] virtual bool get(uint64_t&) {throw std::runtime_error("InputInterface::get(uint64_t&) is not implemented");}

    [[nodiscard]] virtual bool get(int8_t&) {throw std::runtime_error("InputInterface::get(int8_t&) is not implemented");}
    [[nodiscard]] virtual bool get(int16_t&) {throw std::runtime_error("InputInterface::get(int16_t&) is not implemented");}
    [[nodiscard]] virtual bool get(int32_t&) {throw std::runtime_error("InputInterface::get(int32_t&) is not implemented");}
    [[nodiscard]] virtual bool get(int64_t&) {throw std::runtime_error("InputInterface::get(int64_t&) is not implemented");}
    [[nodiscard]] virtual bool get(std::vector<uint8_t>&, size_t) {throw std::runtime_error("InputInterface::get(std::vector<uint8_t>&, size_t) is not implemented");}

    [[nodiscard]] virtual bool open() = 0;
    virtual void close() = 0;
    [[nodiscard]] virtual bool eof() = 0;
    [[nodiscard]] virtual long size() = 0;
    virtual void seek(long) = 0;
};

using InputInterfaceUPtr = std::unique_ptr<InputInterface>;

#endif // __INPUTINTERFACE_H__
