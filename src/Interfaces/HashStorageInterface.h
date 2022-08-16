#ifndef __HASHSTORAGEINTERFACE_H__
#define __HASHSTORAGEINTERFACE_H__

#include <inttypes.h>
#include <memory>

class HashGeneratorInterface;
class CyclicPolinomialRHashStorage;
class InputInterface;

class HashStorageInterface {
public:
    static constexpr size_t NOT_FOUND = std::numeric_limits<size_t>::max();

    virtual ~HashStorageInterface() = default;
    virtual void addHash(HashGeneratorInterface*) = 0;
    virtual bool readHash(InputInterface*) = 0;
    virtual size_t findHash(HashGeneratorInterface*) = 0;
    virtual void clear() = 0;
    virtual size_t size() const noexcept = 0;

    virtual CyclicPolinomialRHashStorage* cyclicPolinomialRHashStorage() noexcept {return nullptr;}
};

using HashStorageInterfaceUPtr = std::unique_ptr<HashStorageInterface>;

#endif // __HASHSTORAGEINTERFACE_H__
