#include "CyclicPolinomialRHash.h"
#include "CharacterMap.h"

CyclicPolinomialRHash::CyclicPolinomialRHash(size_t chunkSize)
: chunkSize_(chunkSize)
, chunk_(chunkSize, 0)
, shiftN_(chunkSize_ % hashValueTypeLength_) {
}

void CyclicPolinomialRHash::add(uint8_t value) {
    if(isFull()) throw std::runtime_error("CyclicPolinomialRHash::add: chunk is full");
    hashValue_ = shift(hashValue_) ^ (chunk_[counter_++] = charToUINT64[value]);
}

CyclicPolinomialRHash::HashValueType CyclicPolinomialRHash::shiftn(CyclicPolinomialRHash::HashValueType value, CyclicPolinomialRHash::HashValueType n) noexcept {
    n %= hashValueTypeLength_;
    return n ? ((value << n) | (value >> (hashValueTypeLength_ - n))) : value;
}

CyclicPolinomialRHash::HashValueType CyclicPolinomialRHash::shift(CyclicPolinomialRHash::HashValueType value) noexcept {
    return (value << 1) | (value >> (hashValueTypeLength_ - 1));
}

void CyclicPolinomialRHash::update(uint8_t value) {
    if(!isFull()) throw std::runtime_error("CyclicPolinomialRHash::update: chunk is not full");
    hashValue_ = shiftn(hashValue_, 1) ^ shiftn(std::exchange(chunk_[counter_ % chunkSize_], charToUINT64[value]), shiftN_) ^ charToUINT64[value];
    ++counter_;
}

void CyclicPolinomialRHash::reset() noexcept {
    hashValue_ = 0;
    //std::fill(chunk_.begin(), chunk_.end(), 0);
    counter_ = 0;
}

void CyclicPolinomialRHash::saveHash(OutputInterfaceUPtr& output) noexcept {
    output->put(hashValue());
}
