#ifndef __OUTPUTINTERFACE_H__
#define __OUTPUTINTERFACE_H__

#include <inttypes.h>
#include <memory>
#include <vector>

class OutputInterface {
public:
    virtual ~OutputInterface() = default;
    virtual void put(int8_t)  {throw std::runtime_error("OutputInterface::put(int8_t) is not implemented");}
    virtual void put(int16_t) {throw std::runtime_error("OutputInterface::put(int16_t) is not implemented");}
    virtual void put(int32_t) {throw std::runtime_error("OutputInterface::put(int32_t) is not implemented");}
    virtual void put(int64_t) {throw std::runtime_error("OutputInterface::put(int64_t) is not implemented");}

    virtual void put(uint8_t)  {throw std::runtime_error("OutputInterface::put(uint8_t) is not implemented");}
    virtual void put(uint16_t) {throw std::runtime_error("OutputInterface::put(uint16_t) is not implemented");}
    virtual void put(uint32_t) {throw std::runtime_error("OutputInterface::put(uint32_t) is not implemented");}
    virtual void put(uint64_t) {throw std::runtime_error("OutputInterface::put(uint64_t) is not implemented");}
    virtual void put(const std::vector<uint8_t>&, size_t) {throw std::runtime_error("OutputInterface::put(std::vector<uint8_t>&, size_t) is not implemented");}

    [[nodiscard]] virtual bool open() = 0;
    virtual void close() = 0;
    virtual void flush() = 0;
};

using OutputInterfaceUPtr = std::unique_ptr<OutputInterface>;

#endif // __OUTPUTINTERFACE_H__
