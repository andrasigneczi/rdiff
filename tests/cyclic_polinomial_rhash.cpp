#include <gtest/gtest.h>
#include "CyclicPolinomialRHash.cpp"
#include "CharacterMap.h"
#include "IOFactory.h"

TEST(CyclicPolinomialRHash, Init) {
    srand((unsigned)time(0));
}

TEST(CyclicPolinomialRHash, Shiftn) {
    ASSERT_EQ(CyclicPolinomialRHash::shiftn(0, 0x4545454545), 0);
    ASSERT_EQ(CyclicPolinomialRHash::shiftn(1, 1), 2);
    ASSERT_EQ(CyclicPolinomialRHash::shiftn(1, 63), 0x8000000000000000);
    ASSERT_EQ(CyclicPolinomialRHash::shiftn(1, 64), 1);
    ASSERT_EQ(CyclicPolinomialRHash::shiftn(1, 65), 2);
    ASSERT_EQ(CyclicPolinomialRHash::shiftn(1, 128), 1);
}

TEST(CyclicPolinomialRHash, Add) {
    CyclicPolinomialRHash hash(600);
    hash.add(10);
    ASSERT_EQ(hash.hashValue(), charToUINT64[10]);
    hash.add(11);
    ASSERT_EQ(hash.hashValue(), (CyclicPolinomialRHash::shiftn(charToUINT64[10], 1)^charToUINT64[11]));
    hash.add(12);
    ASSERT_EQ(hash.hashValue(), (CyclicPolinomialRHash::shiftn(CyclicPolinomialRHash::shiftn(charToUINT64[10], 1), 1)^CyclicPolinomialRHash::shiftn(charToUINT64[11], 1)^charToUINT64[12]));
    for(int i = 13; i < 610; ++i) hash.add((uint8_t)(i % 256));
    ASSERT_TRUE(hash.isFull());
    CyclicPolinomialRHash::HashValueType hashValue = 0;
    for(size_t i = 0; i < 600; ++i) {
        hashValue ^= CyclicPolinomialRHash::shiftn(charToUINT64[(i + 10) % 256], 599 - i);
    }
    ASSERT_EQ(hashValue, hash.hashValue());
}

TEST(CyclicPolinomialRHash, Update) {
    size_t chunkSize = 1600;
    CyclicPolinomialRHash hash(chunkSize);
    for(size_t i = 45; i < chunkSize + 45; ++i) hash.add((uint8_t)(i % 256));
    ASSERT_TRUE(hash.isFull());

    auto hashValue = hash.hashValue();
    uint8_t testValue = (uint8_t)(rand()%256);
    hash.update(testValue);
    size_t shiftN = chunkSize % sizeof(CyclicPolinomialRHash::HashValueType);

    ASSERT_EQ(hash.hashValue(), CyclicPolinomialRHash::shiftn(hashValue, 1) ^ CyclicPolinomialRHash::shiftn(charToUINT64[45], shiftN) ^ charToUINT64[testValue] ) << "Test value '" << testValue << "' failed";
}

TEST(CyclicPolinomialRHash, SaveHash) {
    size_t chunkSize = 6;
    CyclicPolinomialRHash hash(chunkSize);
    for(size_t i = 0; i < chunkSize; ++i) hash.add((uint8_t)(rand() % 256));
    ASSERT_TRUE(hash.isFull());

    ASSERT_EQ(system("rm -f save_hash_test"), 0);
    CyclicPolinomialRHash::HashValueType hashValue;

    OutputInterfaceUPtr output = IOFactory::createOutput("save_hash_test");
    ASSERT_TRUE(output->open());
    hash.saveHash(output);
    output->flush();
    output->close();

    InputInterfaceUPtr input = IOFactory::createInput("save_hash_test");
    ASSERT_TRUE(input->open());
    ASSERT_TRUE(input->get(hashValue));
    input->close();
    ASSERT_EQ(hashValue, hash.hashValue());
    ASSERT_EQ(system("rm -f save_hash_test"), 0);
}
