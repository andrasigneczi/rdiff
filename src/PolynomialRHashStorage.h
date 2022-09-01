#ifndef __POLINOMIALRHASHSTORAGE_H__
#define __POLINOMIALRHASHSTORAGE_H__

#include "PolynomialRHash.h"
#include "HashStorageInterface.h"
#include "InputInterface.h"

template<typename T>
class PolinomialRHashStorage final : public HashStorageInterface {
    friend class RdiffBuilder;
    PolinomialRHashStorage() = default;
public:
    void addHash(HashGeneratorInterface* i) override;
    [[nodiscard]] size_t findHash(HashGeneratorInterface* inf) override;
    void clear() override {signatureStorage_.clear();}
    [[nodiscard]] size_t size() const noexcept override {return signatureStorage_.size();}
    [[nodiscard]] bool readHash(InputInterface* input) override;

private:
    std::vector<typename PolinomialRHash<T>::HasValueType> signatureStorage_;
};

template<typename T>
void PolinomialRHashStorage<T>::addHash(HashGeneratorInterface* i) {
    PolinomialRHash<T>* h = (PolinomialRHash<T>*)i;
    signatureStorage_.push_back(h->hashValue());
}

template<typename T>
size_t PolinomialRHashStorage<T>::findHash(HashGeneratorInterface* inf) {
    PolinomialRHash<T>* h = (PolinomialRHash<T>*)inf;
    if(auto pos = std::find(signatureStorage_.begin(), signatureStorage_.end(), h->hashValue()); pos != signatureStorage_.end()) {
        return (size_t)std::distance(signatureStorage_.begin(), pos);
    }
    return NOT_FOUND;
}

template<typename T>
bool PolinomialRHashStorage<T>::readHash(InputInterface* input) {
    typename PolinomialRHash<T>::HasValueType v;
    if(input->get(v)) {
        signatureStorage_.push_back(v);
        return true;
    }
    return false;
}

#endif // __POLINOMIALRHASHSTORAGE_H__
