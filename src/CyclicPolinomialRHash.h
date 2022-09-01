#ifndef __CYCLICPOLINOMIALRHASH_H__
#define __CYCLICPOLINOMIALRHASH_H__

#include <array>
#include "HashGeneratorInterface.h"
#include <vector>

class CyclicPolinomialRHash final : public HashGeneratorInterface {
public:
    using HashValueType = uint64_t;
    CyclicPolinomialRHash(size_t chunkSize);

    void add(uint8_t value) override;
    void update(uint8_t value) override;
    [[nodiscard]] bool isFull() const noexcept override {return chunkSize_ <= counter_;}
    void reset() noexcept override;
    void saveHash(OutputInterfaceUPtr& output) noexcept override;
    [[nodiscard]] Type hashFunctionType() const noexcept override {return Type::CYCLIC_POLINOMIAL;}
    [[nodiscard]] CyclicPolinomialRHash* cyclicPolinomialRHash() noexcept override {return this;}


    [[nodiscard]] HashValueType hashValue() noexcept {return hashValue_;}
    [[nodiscard]] static HashValueType shiftn(HashValueType value, HashValueType n) noexcept;
    [[nodiscard]] static HashValueType shift(HashValueType value) noexcept;

private:

    HashValueType hashValue_{};
    const size_t chunkSize_;
    size_t counter_{};
    std::vector<HashValueType> chunk_;
    static constexpr int hashValueTypeLength_ = sizeof(HashValueType) << 3;
    const HashValueType shiftN_;
};

#endif // __CYCLICPOLINOMIALRHASH_H__
