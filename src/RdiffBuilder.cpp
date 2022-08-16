#include "RdiffBuilder.h"
#include "IOFactory.h"
#include "PolynomialRHash.h"
#include "PolynomialRHashStorage.h"
#include "CyclicPolinomialRHashStorage.h"
#include "CyclicPolinomialRHash.h"
#include "ClockFactory.h"
#include "CoutLogger.h"

#include  <iostream>

RdiffUPtr RdiffBuilder::build(ParametersUPtr params) {
    RdiffUPtr rdiff = RdiffUPtr(new Rdiff);
    auto rdiffP = rdiff.get();

    switch(params->function()) {
    case Parameters::Function::SIGNATURE: {
        rdiff->setInput1(IOFactory::createInput(params->oldFileName()));
        rdiff->setOutput(IOFactory::createOutput(params->signatureFileName()));
        setHashFunction(rdiff, params);
        rdiff->setTask(std::bind(&Rdiff::generateSignature, rdiffP));
        break;
    }
    case Parameters::Function::DELTA: {
        rdiff->setInput1(IOFactory::createInput(params->signatureFileName()));
        rdiff->setInput2(IOFactory::createInput(params->newFileName()));
        rdiff->setOutput(IOFactory::createOutput(params->deltaFileName()));
        rdiff->setTask([rdiffP](){rdiffP->loadSignature(); rdiffP->generateDelta();});
        break;
    }
    case Parameters::Function::PATCH: {
        rdiff->setInput1(IOFactory::createInput(params->oldFileName()));
        rdiff->setInput2(IOFactory::createInput(params->deltaFileName()));
        rdiff->setOutput(IOFactory::createOutput(params->newFileName()));
        rdiff->setTask([rdiffP](){rdiffP->loadDelta(); rdiffP->generatePatchedOutput();});
        break;
    }
    case Parameters::Function::INVALID:
        throw std::runtime_error("RdiffBuilder::build: invalid funtion");
    }

    ClockFactory cf(params->statistics() ? ClockFactory::ClockType::REAL : ClockFactory::ClockType::DUMMY);
    rdiff->setClock(cf.create(""));

    if(params->debug() || params->verbose()) {
        rdiff->setLogger(LoggerInterfaceUPtr(new CoutLogger(params->debug() ? CoutLogger::Type::DEBUG : CoutLogger::Type::VERBOSE)));
    }

    return rdiff;
}

void RdiffBuilder::setHashFunction(RdiffUPtr& rdiff, const ParametersUPtr& params) {
    switch(params->hashFunction()) {
    case Parameters::HashFunction::POLYNOMIAL_ROLLING_HASH:
        rdiff->setHashGenerator(HashGeneratorInterfaceUPtr( new PolinomialRHash<Rdiff::HashValueType>(Rdiff::blockSize_, Rdiff::prime_, Rdiff::multipler_)));
        rdiff->setSignatureStorage(HashStorageInterfaceUPtr(new PolinomialRHashStorage<Rdiff::HashValueType>()));
        break;
    case Parameters::HashFunction::CYCLIC_POLYNOMIAL_ROLLING_HASH:
        rdiff->setHashGenerator(HashGeneratorInterfaceUPtr( new CyclicPolinomialRHash(Rdiff::blockSize_)));
        rdiff->setSignatureStorage(HashStorageInterfaceUPtr(new CyclicPolinomialRHashStorage));
        break;
    }
}

void RdiffBuilder::changeHashFunction(Rdiff* rdiff, uint8_t hashFunctionType) {
    if(hashFunctionType == (uint8_t)HashGeneratorInterface::Type::POLINOMIAL) {
        rdiff->setHashGenerator(HashGeneratorInterfaceUPtr( new PolinomialRHash<Rdiff::HashValueType>(Rdiff::blockSize_, Rdiff::prime_, Rdiff::multipler_)));
        rdiff->setSignatureStorage(HashStorageInterfaceUPtr(new PolinomialRHashStorage<Rdiff::HashValueType>()));
    } else if(hashFunctionType == (uint8_t)HashGeneratorInterface::Type::CYCLIC_POLINOMIAL) {
        rdiff->setHashGenerator(HashGeneratorInterfaceUPtr( new CyclicPolinomialRHash(Rdiff::blockSize_)));
        rdiff->setSignatureStorage(HashStorageInterfaceUPtr(new CyclicPolinomialRHashStorage));
    } else {
        throw std::runtime_error("Invalid hash function id");
    }
}
