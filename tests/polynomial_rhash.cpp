#include <gtest/gtest.h>
#include "PolynomialRHash.h"
#include "IOFactory.h"

namespace {
    using rhType = int32_t;
    PolinomialRHashUPtr<rhType> rollingHash;
    int chunkSize;
    int prime;
    int multipler;
}

TEST(PolinomialRHash, Add1) {
    chunkSize = 1;
    prime = 113;
    multipler = 10;
    rollingHash = std::make_unique<PolinomialRHash<rhType>>(chunkSize, prime, multipler);
    ASSERT_EQ(rollingHash->hashFunctionType(), HashGeneratorInterface::Type::POLINOMIAL);
    ASSERT_FALSE(rollingHash->isFull());
    rollingHash->add(11);
    ASSERT_EQ(rollingHash->hashValue(), 11);
    ASSERT_TRUE(rollingHash->isFull());
}

TEST(PolinomialRHash, Add2) {
    chunkSize = 2;
    rollingHash = std::make_unique<PolinomialRHash<rhType>>(chunkSize, prime, multipler);
    ASSERT_FALSE(rollingHash->isFull());
    rollingHash->add(11);
    ASSERT_EQ(rollingHash->hashValue(), 11);
    ASSERT_FALSE(rollingHash->isFull());

    rollingHash->add(255);
    ASSERT_EQ(rollingHash->hashValue(), 26);
    ASSERT_TRUE(rollingHash->isFull());
}

TEST(PolinomialRHash, Add3) {
    chunkSize = 3;
    rollingHash = std::make_unique<PolinomialRHash<rhType>>(chunkSize, prime, multipler);
    rollingHash->add(255);
    ASSERT_THROW(rollingHash->update(255), std::runtime_error);
    ASSERT_EQ(rollingHash->hashValue(), 29);

    rollingHash->add(255);
    ASSERT_EQ(rollingHash->hashValue(), 93); // ((255%113)*10 + 255)%113

    ASSERT_FALSE(rollingHash->isFull());
    rollingHash->add(255);
    ASSERT_EQ(rollingHash->hashValue(), 55); // ((((255%113)*10 + 255)%113)*10+255)%113
    ASSERT_TRUE(rollingHash->isFull());

    ASSERT_THROW(rollingHash->add(255), std::runtime_error);
}

TEST(PolinomialRHash, Update1) {
    ASSERT_EQ(rollingHash->hashValue(), 55);
    rollingHash->update(255);
    ASSERT_EQ(rollingHash->hashValue(), 55); // ((55 - 255 * 100 + 113) * 10 ) % 113) + (255 % 113)
    rollingHash->update(255);
    ASSERT_EQ(rollingHash->hashValue(), 55);
}

TEST(PolinomialRHash, SaveHash) {
    ASSERT_EQ(system("rm -f save_hash_test"), 0);
    PolinomialRHash<rhType>::HasValueType hashValue;

    OutputInterfaceUPtr output = IOFactory::createOutput("save_hash_test");
    ASSERT_TRUE(output->open());
    rollingHash->saveHash(output);
    output->flush();
    output->close();

    InputInterfaceUPtr input = IOFactory::createInput("save_hash_test");
    ASSERT_TRUE(input->open());
    ASSERT_TRUE(input->get(hashValue));
    input->close();
    ASSERT_EQ(hashValue, rollingHash->hashValue());
    ASSERT_EQ(system("rm -f save_hash_test"), 0);
}
