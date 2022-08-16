#ifndef __CYCLICPOLINOMIALRHASHSTORAGE_H__
#define __CYCLICPOLINOMIALRHASHSTORAGE_H__

#include "HashStorageInterface.h"
#include "CyclicPolinomialRHash.h"
#include <vector>
#include <unordered_map>

class HashGeneratorInterface;
class InputInterface;

class CyclicPolinomialRHashStorage final : public HashStorageInterface {
    friend class RdiffBuilder;
    CyclicPolinomialRHashStorage() = default;
public:
    void addHash(HashGeneratorInterface*) override;
    bool readHash(InputInterface*) override;
    size_t findHash(HashGeneratorInterface*) override;
    void clear() override {signatureStorage_.clear();}
    size_t size() const noexcept override {return signatureStorage_.size();}

    CyclicPolinomialRHashStorage* cyclicPolinomialRHashStorage() noexcept override {return this;}

private:
    std::unordered_map<typename CyclicPolinomialRHash::HashValueType, size_t> signatureStorage_;
};

#endif // __CYCLICPOLINOMIALRHASHSTORAGE_H__
