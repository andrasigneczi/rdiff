#include "CyclicPolinomialRHashStorage.h"
#include "InputInterface.h"
#include <iostream>

void CyclicPolinomialRHashStorage::addHash(HashGeneratorInterface* h) {
    CyclicPolinomialRHash* h2 = h->cyclicPolinomialRHash();
    signatureStorage_.emplace(h2->hashValue(), signatureStorage_.size());
}

bool CyclicPolinomialRHashStorage::readHash(InputInterface* input) {
    typename CyclicPolinomialRHash::HashValueType value;
    if(!input->get(value)) return false;
    signatureStorage_.emplace(value, signatureStorage_.size());
    return true;
}

size_t CyclicPolinomialRHashStorage::findHash(HashGeneratorInterface* inf) {
    CyclicPolinomialRHash* h = inf->cyclicPolinomialRHash();

    if(auto pos = signatureStorage_.find(h->hashValue()); pos != signatureStorage_.end()) {
        return pos->second;
    }
    return NOT_FOUND;
}
