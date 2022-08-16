#include <gtest/gtest.h>
#include "Parameters.h"
#include <string>

using namespace std::string_literals;

namespace {
}

/*
rdiff signature TODO1.txt TODO1.txt.sig
rdiff delta TODO1.txt.sig TODO2.txt TODO1.txt.del
rdiff patch TODO1.txt TODO1.txt.del NEWTODO2.txt
 */
TEST(Parameters, T1_valid) {
    constexpr int paramcount = 5;
    const char *argv[paramcount] = {"rdiff", "-v", "signature", "F1", "F1.sig"};
    Parameters p(paramcount, argv);
    ASSERT_TRUE(p.verbose());
    ASSERT_EQ(p.function(), Parameters::Function::SIGNATURE);
    ASSERT_EQ(p.oldFileName(), "F1"s);
    ASSERT_EQ(p.signatureFileName(), "F1.sig"s);
    ASSERT_TRUE(p.valid());
}

TEST(Parameters, T2_valid) {
    constexpr int paramcount = 4;
    const char *argv[paramcount] = {"rdiff", "signature", "F1", "F1.sig"};
    Parameters p(paramcount, argv);
    ASSERT_FALSE(p.verbose());
    ASSERT_EQ(p.function(), Parameters::Function::SIGNATURE);
    ASSERT_EQ(p.oldFileName(), "F1"s);
    ASSERT_EQ(p.signatureFileName(), "F1.sig"s);
    ASSERT_TRUE(p.valid());
}

TEST(Parameters, T3_valid) {
    constexpr int paramcount = 5;
    const char *argv[paramcount] = {"rdiff", "delta", "F1.sig", "F2", "F1.del"};
    Parameters p(paramcount, argv);
    ASSERT_FALSE(p.verbose());
    ASSERT_EQ(p.function(), Parameters::Function::DELTA);
    ASSERT_EQ(p.signatureFileName(), "F1.sig"s);
    ASSERT_EQ(p.newFileName(), "F2"s);
    ASSERT_EQ(p.deltaFileName(), "F1.del"s);
    ASSERT_TRUE(p.valid());
}

TEST(Parameters, T4_invalid) {
    constexpr int paramcount = 6;
    const char *argv[paramcount] = {"rdiff", "-v", "signature", "F1", "F1.sig", "blabla"};
    Parameters p(paramcount, argv);
    ASSERT_TRUE(p.verbose());
    ASSERT_EQ(p.function(), Parameters::Function::SIGNATURE);
    ASSERT_EQ(p.oldFileName(), "F1"s);
    ASSERT_EQ(p.signatureFileName(), "F1.sig"s);
    ASSERT_FALSE(p.valid());
    ASSERT_EQ(p.error(), "Invalid parameter count"s);
}

TEST(Parameters, T5_invalid) {
    constexpr int paramcount = 4;
    const char *argv[paramcount] = {"rdiff", "-v", "signature", "F1"};
    Parameters p(paramcount, argv);
    ASSERT_TRUE(p.verbose());
    ASSERT_EQ(p.function(), Parameters::Function::SIGNATURE);
    ASSERT_EQ(p.oldFileName(), "F1"s);
    ASSERT_NE(p.signatureFileName(), "F1.sig"s);
    ASSERT_FALSE(p.valid());
    ASSERT_EQ(p.error(), "Invalid parameter count"s);
}

TEST(Parameters, T6_invalid) {
    constexpr int paramcount = 4;
    const char *argv[paramcount] = {"rdiff", "-v", "delta", "F1.sig"};
    Parameters p(paramcount, argv);
    ASSERT_TRUE(p.verbose());
    ASSERT_EQ(p.function(), Parameters::Function::DELTA);
    ASSERT_EQ(p.signatureFileName(), "F1.sig"s);
    ASSERT_NE(p.newFileName(), "F2"s);
    ASSERT_NE(p.deltaFileName(), "F1.del"s);
    ASSERT_FALSE(p.valid());
    ASSERT_EQ(p.error(), "Invalid parameter count"s);
}

TEST(Parameters, T7_invalid) {
    constexpr int paramcount = 4;
    const char *argv[paramcount] = {"rdiff", "-v", "patch", "F1.sig"};
    Parameters p(paramcount, argv);
    ASSERT_TRUE(p.verbose());
    ASSERT_EQ(p.function(), Parameters::Function::PATCH);
    ASSERT_FALSE(p.valid());
    ASSERT_EQ(p.error(), "Invalid parameter count"s);
}

TEST(Parameters, T8_valid) {
    constexpr int paramcount = 6;
    const char *argv[paramcount] = {"rdiff", "-v", "-v", "signature", "F1", "F1.sig"};
    Parameters p(paramcount, argv);
    ASSERT_TRUE(p.verbose());
    ASSERT_EQ(p.function(), Parameters::Function::SIGNATURE);
    ASSERT_EQ(p.oldFileName(), "F1"s);
    ASSERT_EQ(p.signatureFileName(), "F1.sig"s);
    ASSERT_TRUE(p.valid());
}
