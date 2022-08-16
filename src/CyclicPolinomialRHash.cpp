#include "CyclicPolinomialRHash.h"
#include "CharacterMap.h"

CyclicPolinomialRHash::CyclicPolinomialRHash(size_t chunkSize)
: chunkSize_(chunkSize)
, chunk_(chunkSize, 0)
, shiftN_(chunkSize_ % hashValueTypeLength_) {
}

void CyclicPolinomialRHash::add(uint8_t value) {
    if(isFull()) throw std::runtime_error("CyclicPolinomialRHash::add: chunk is full");
    chunk_[counter_++] = charToUINT64[value];
    hashValue_ = shiftn(hashValue_, 1) ^ charToUINT64[value];
}

CyclicPolinomialRHash::HashValueType CyclicPolinomialRHash::shiftn(CyclicPolinomialRHash::HashValueType value, CyclicPolinomialRHash::HashValueType n) noexcept {
    n %= hashValueTypeLength_;
    return n ? ((value << n) | (value >> (hashValueTypeLength_ - n))) : value;
}

void CyclicPolinomialRHash::update(uint8_t value) {
    if(!isFull()) throw std::runtime_error("CyclicPolinomialRHash::update: chunk is not full");
    HashValueType oldValue = std::exchange(chunk_[counter_ % chunkSize_], charToUINT64[value]);
    hashValue_ = shiftn(hashValue_, 1) ^ shiftn(oldValue, shiftN_) ^ charToUINT64[value];
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
