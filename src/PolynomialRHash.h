#ifndef __POLINOMIALRHASH_H__
#define __POLINOMIALRHASH_H__

#include <memory>
#include <queue>
#include "HashGeneratorInterface.h"
#include "HashStorageInterface.h"
#include "InputInterface.h"

template<typename T>
class PolinomialRHash final : public HashGeneratorInterface {
public:
    using HasValueType = T;

    PolinomialRHash(T chunkSize, T prime, T multipler) noexcept;

    [[nodiscard]]T hashValue() const noexcept {return hashValue_;}

    void add(uint8_t value) override;
    void update(uint8_t newValue) override;

    bool isFull() const noexcept override {return chunkSize_ == chunkPos_;}
    void reset() noexcept override;

    void saveHash(OutputInterfaceUPtr& output) noexcept override;

    Type hashFunctionType() const noexcept override {return Type::POLINOMIAL;}

private:
    T powMod(T m) noexcept;
    T mul(T a, T b) noexcept;
    T mul2(T a, T b) noexcept;

    T hashValue_{};
    const T chunkSize_;
    T chunkPos_{};
    const T prime_;
    const T multipler_;
    std::queue<uint8_t> queue;
    const T powModVal_;
};

template<typename T>
using PolinomialRHashUPtr = std::unique_ptr<PolinomialRHash<T>>;

template<typename T>
PolinomialRHash<T>::PolinomialRHash(T chunkSize, T prime, T multipler) noexcept
: chunkSize_(chunkSize)
, prime_(prime)
, multipler_(multipler)
, powModVal_(powMod(chunkSize_ - 1)) {

}

// (A * B) mod C = ((A mod C) * (B mod C)) MOD C
// (A + B) mod C = (A mod C + B mod C) mod C
// (A - B) mod C = (A mod C - B mod C) mod C

template<typename T>
T PolinomialRHash<T>::mul(T a, T b) noexcept {
    if constexpr (std::is_signed<T>::value) {
        return (T)(((int64_t)(a % prime_) * (int64_t)(b % prime_)) % (int64_t)prime_);
    }
    return (T)(((uint64_t)(a % prime_) * (uint64_t)(b % prime_)) % (uint64_t)prime_);
}

template<typename T>
T PolinomialRHash<T>::mul2(T a, T b) noexcept {
    if constexpr (std::is_signed<T>::value) {
        return (T)(((int64_t)(a % prime_) * (int64_t)b) % (int64_t)prime_);
    }
    return (T)(((uint64_t)(a % prime_) * (uint64_t)b) % (uint64_t)prime_);
}

template<typename T>
T PolinomialRHash<T>::powMod(T m) noexcept {
    T n = 1;
    for(T i = 0; i < m; ++i) {
        n = mul(n, multipler_);
    }
    return n;
}

template<typename T>
void PolinomialRHash<T>::add(uint8_t value) {
    if(chunkSize_ == chunkPos_) throw std::runtime_error("PolinomialRHash::add: chunk is full");
    queue.push(value);
    hashValue_ = (mul2(hashValue_, multipler_) + (T)value) % prime_;
    ++chunkPos_;
}

template<typename T>
void PolinomialRHash<T>::update(uint8_t newValue) {
    if(chunkSize_ != chunkPos_) throw std::runtime_error("PolinomialRHash::update: chunk is not full");
    queue.push(newValue);
    auto oldValue = queue.front();
    queue.pop();
    hashValue_ = hashValue_ + prime_- mul((T)oldValue, powModVal_); // negative value is not allowed here
    hashValue_ = (mul(hashValue_, multipler_) + ((T)newValue % prime_)) % prime_;
}

template<typename T>
void PolinomialRHash<T>::reset() noexcept {
    chunkPos_ = 0;
    hashValue_ = 0;
    queue = std::queue<uint8_t>();
}

template<typename T>
void PolinomialRHash<T>::saveHash(OutputInterfaceUPtr& output) noexcept {
    output->put(hashValue());
}

#endif // __POLINOMIALRHASH_H__
