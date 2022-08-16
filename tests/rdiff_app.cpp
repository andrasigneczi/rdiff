#include <gtest/gtest.h>

using namespace std::string_literals;

namespace {
    constexpr int folderCount = 12;
    constexpr int binaryTestStarts = 10;
}

TEST(Rdiff_app, Init) {
    for(int i = 0; i < folderCount; ++i) {
        std::string istr = std::to_string(i);
        std::string extension;
        if(i < binaryTestStarts) extension = ".txt";
        std::string command = "rm -f test_cases/t" + istr + "/sig_file " +
                                    "test_cases/t" + istr + "/delta_file " +
                                    "test_cases/t" + istr + "/patched_file" + extension + " " +
                                    "test_cases/t" + istr + "/output_gen_sign_h1.txt " +
                                    "test_cases/t" + istr + "/output_gen_delta_h1.txt " +
                                    "test_cases/t" + istr + "/output_gen_patch_h1.txt";
        ASSERT_EQ(system(command.c_str()), 0) << "ERROR: rm failed in test_cases/t" << i << " folder";
    }
}

TEST(Rdiff_app, T_signature_h1) {
    for(int i = 0; i < folderCount; ++i) {
        std::string istr = std::to_string(i);
        std::string extension;
        if(i < binaryTestStarts) extension = ".txt";
        std::string command = "../src/rdiff -vv -hash 1 signature test_cases/t" + istr + "/base_file" + extension + " test_cases/t" + istr + "/sig_file > test_cases/t" + istr + "/output_gen_sign_h1.txt";
        ASSERT_EQ(system(command.c_str()), 0) << "ERROR: signature file error in test_cases/t" << i << " folder";

        std::string commandDiff = "diff ./test_cases/t" + std::to_string(i) + "/output_gen_sign_h1.txt ./test_cases/t" +
                std::to_string(i) + "/output_gen_sign_h1_o.txt";
        EXPECT_EQ(system(commandDiff.c_str()), 0) << "ERROR: Invalid result in test_cases/t" << i << " folder\n";
    }
}

TEST(Rdiff_app, T_delta_h1) {
    for(int i = 0; i < folderCount; ++i) {
        std::string istr = std::to_string(i);
        std::string extension;
        if(i < binaryTestStarts) extension = ".txt";
        std::string command = "../src/rdiff -vv -hash 1 delta test_cases/t" + istr + "/sig_file test_cases/t" + istr + "/new_file" + extension + " test_cases/t" + istr + "/delta_file > test_cases/t" + istr + "/output_gen_delta_h1.txt";
        ASSERT_EQ(system(command.c_str()), 0) << "ERROR: delta file error in test_cases/t" << i << " folder";

        std::string commandDiff = "diff ./test_cases/t" + std::to_string(i) + "/output_gen_delta_h1.txt ./test_cases/t" +
                std::to_string(i) + "/output_gen_delta_h1_o.txt";
        EXPECT_EQ(system(commandDiff.c_str()), 0) << "ERROR: Invalid result in test_cases/t" << i << " folder\n";
    }
}

TEST(Rdiff_app, T_patch_h1) {
    for(int i = 0; i < folderCount; ++i) {
        std::string istr = std::to_string(i);
        std::string extension;
        if(i < binaryTestStarts) extension = ".txt";
        std::string command = "../src/rdiff -vv -hash 1 patch test_cases/t" + istr + "/base_file" + extension + " test_cases/t" + istr + "/delta_file test_cases/t" + istr + "/patched_file" + extension + " > test_cases/t" + istr + "/output_gen_patch_h1.txt";
        ASSERT_EQ(system(command.c_str()), 0) << "ERROR: delta file error in test_cases/t" << i << " folder";

        std::string commandDiff = "diff ./test_cases/t" + std::to_string(i) + "/output_gen_patch_h1.txt ./test_cases/t" +
                std::to_string(i) + "/output_gen_patch_h1_o.txt";
        EXPECT_EQ(system(commandDiff.c_str()), 0) << "ERROR: Invalid result in test_cases/t" << i << " folder\n";
    }
}

TEST(Rdiff_app, T_signature_h2) {
    for(int i = 0; i < folderCount; ++i) {
        std::string istr = std::to_string(i);
        std::string extension;
        if(i < binaryTestStarts) extension = ".txt";
        std::string command = "../src/rdiff -v -hash 2 signature test_cases/t" + istr + "/base_file" + extension + " test_cases/t" + istr + "/sig_file > test_cases/t" + istr + "/output_gen_sign_h2.txt";
        ASSERT_EQ(system(command.c_str()), 0) << "ERROR: signature file error in test_cases/t" << i << " folder";

        std::string commandDiff = "diff ./test_cases/t" + std::to_string(i) + "/output_gen_sign_h2.txt ./test_cases/t" +
                std::to_string(i) + "/output_gen_sign_h2_o.txt";
        EXPECT_EQ(system(commandDiff.c_str()), 0) << "ERROR: Invalid result in test_cases/t" << i << " folder\n";
    }
}

TEST(Rdiff_app, T_delta_h2) {
    for(int i = 0; i < folderCount; ++i) {
        std::string istr = std::to_string(i);
        std::string extension;
        if(i < binaryTestStarts) extension = ".txt";
        std::string command = "../src/rdiff -v -hash 2 delta test_cases/t" + istr + "/sig_file test_cases/t" + istr + "/new_file" + extension + " test_cases/t" + istr + "/delta_file > test_cases/t" + istr + "/output_gen_delta_h2.txt";
        ASSERT_EQ(system(command.c_str()), 0) << "ERROR: delta file error in test_cases/t" << i << " folder";

        std::string commandDiff = "diff ./test_cases/t" + std::to_string(i) + "/output_gen_delta_h2.txt ./test_cases/t" +
                std::to_string(i) + "/output_gen_delta_h2_o.txt";
        EXPECT_EQ(system(commandDiff.c_str()), 0) << "ERROR: Invalid result in test_cases/t" << i << " folder\n";
    }
}

TEST(Rdiff_app, T_patch_h2) {
    for(int i = 0; i < folderCount; ++i) {
        std::string istr = std::to_string(i);
        std::string extension;
        if(i < binaryTestStarts) extension = ".txt";
        std::string command = "../src/rdiff -v -hash 2 patch test_cases/t" + istr + "/base_file" + extension + " test_cases/t" + istr + "/delta_file test_cases/t" + istr + "/patched_file" + extension + " > test_cases/t" + istr + "/output_gen_patch_h2.txt";
        ASSERT_EQ(system(command.c_str()), 0) << "ERROR: delta file error in test_cases/t" << i << " folder";

        std::string commandDiff = "diff ./test_cases/t" + std::to_string(i) + "/output_gen_patch_h2.txt ./test_cases/t" +
                std::to_string(i) + "/output_gen_patch_h2_o.txt";
        EXPECT_EQ(system(commandDiff.c_str()), 0) << "ERROR: Invalid result in test_cases/t" << i << " folder\n";
    }
}
