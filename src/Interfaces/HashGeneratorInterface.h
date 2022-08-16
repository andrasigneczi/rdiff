#ifndef __HASHGENERATORINTERFACE_H__
#define __HASHGENERATORINTERFACE_H__

#include "OutputInterface.h"
#include <memory>

class CyclicPolinomialRHash;

class HashGeneratorInterface {
public:
    enum class Type : uint8_t {
        POLINOMIAL,
        CYCLIC_POLINOMIAL
    };

    virtual ~HashGeneratorInterface() = default;

    virtual void add(uint8_t value) = 0;
    virtual void update(uint8_t value) = 0;
    virtual bool isFull() const noexcept = 0;
    virtual void reset() noexcept = 0;
    virtual void saveHash(OutputInterfaceUPtr& output) noexcept = 0;
    virtual Type hashFunctionType() const noexcept = 0;

    virtual CyclicPolinomialRHash* cyclicPolinomialRHash() noexcept {return nullptr;}
private:
};

using HashGeneratorInterfaceUPtr = std::unique_ptr<HashGeneratorInterface>;

#endif // __HASHGENERATORINTERFACE_H__
