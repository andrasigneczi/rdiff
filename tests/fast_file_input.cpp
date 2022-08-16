#include <gtest/gtest.h>
#include "FastFileInput.h"
#include <string.h>

namespace {
    InputInterfaceUPtr fastFileInput;
    constexpr size_t expectedFileSize = 11357;
    std::unique_ptr<uint8_t[]> testBuffer;
    size_t testBufferPosition_{};
}

TEST(FastFileInput, Init) {
    testBuffer = std::make_unique<uint8_t[]>(expectedFileSize);
    fastFileInput = InputInterfaceUPtr(new FastFileInput("test_cases/t0/base_file.txt"));
    ASSERT_TRUE(fastFileInput->open());
}

TEST(FastFileInput, FileSize) {
    ASSERT_EQ(fastFileInput->size(), expectedFileSize);
}

TEST(FastFileInput, GetByte) {
    uint8_t c;
    for(size_t i = 0; i < expectedFileSize; ++i) {
        ASSERT_TRUE(fastFileInput->get(c));
        testBuffer[testBufferPosition_++] = c;
    }
    ASSERT_FALSE(fastFileInput->eof());
    ASSERT_FALSE(fastFileInput->get(c));
    ASSERT_TRUE(fastFileInput->eof());
}

TEST(FastFileInput, Seek) {
    ASSERT_NO_THROW(fastFileInput->seek(0));
}

TEST(FastFileInput, GetInt) {
    uint32_t c;
    uint32_t b;
    testBufferPosition_ = 0;
    for(size_t i = 0; i < expectedFileSize / sizeof(c); ++i) {
        ASSERT_TRUE(fastFileInput->get(c));
        memcpy(&b, &testBuffer[testBufferPosition_], sizeof(c));
        ASSERT_EQ(b, c);
        testBufferPosition_ += sizeof(c);
    }
    ASSERT_FALSE(fastFileInput->get(c));
    ASSERT_FALSE(fastFileInput->eof());
    uint8_t cc;
    ASSERT_TRUE(fastFileInput->get(cc));
    ASSERT_TRUE(fastFileInput->eof());
}

TEST(FastFileInput, Close) {
    fastFileInput->close();
}
