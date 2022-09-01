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
    [[nodiscard]] bool readHash(InputInterface*) override;
    [[nodiscard]] size_t findHash(HashGeneratorInterface*) override;
    void clear() override {signatureStorage_.clear();}
    [[nodiscard]] size_t size() const noexcept override {return signatureStorage_.size();}

    [[nodiscard]] CyclicPolinomialRHashStorage* cyclicPolinomialRHashStorage() noexcept override {return this;}

private:
    std::unordered_map<typename CyclicPolinomialRHash::HashValueType, size_t> signatureStorage_;
};

#endif // __CYCLICPOLINOMIALRHASHSTORAGE_H__
