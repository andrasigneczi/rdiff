#include <gtest/gtest.h>
#include "RdiffBuilder.h"
#include "Parameters.h"
#include <fstream>
#include <algorithm>

using namespace std::string_literals;

namespace {
    ParametersUPtr p;
    RdiffUPtr rdiff;
    constexpr int folderCount = 12;
    constexpr int binaryTestStarts = 10;
    std::string hashFunction;

    void generateSignature(int folderIndex) try {
        std::string istr = std::to_string(folderIndex);
        std::string extension;
        if(folderIndex < binaryTestStarts) extension = ".txt";
        std::string baseFileName = "test_cases/t" + istr + "/base_file" + extension;
        std::string sigFileName = "test_cases/t" + istr + "/sig_file";

        constexpr int paramcount = 6;
        const char *argv[paramcount] = {"rdiff", "signature", "-hash", hashFunction.c_str(), baseFileName.c_str(), sigFileName.c_str()};

        p = std::make_unique<Parameters>(paramcount, argv);

        rdiff = RdiffBuilder::build(std::move(p));
        rdiff->execute();
    } catch(std::runtime_error& r) {
        std::cout << r.what() << "\n";
        std::cout << "Test folder: t" << std::to_string(folderIndex) << "\n";
        throw;
    }


    void generateDelta(int folderIndex) try {
        std::string istr = std::to_string(folderIndex);
        std::string extension;
        if(folderIndex < binaryTestStarts) extension = ".txt";
        std::string sigFileName = "test_cases/t" + istr + "/sig_file";
        std::string deltaFileName = "test_cases/t" + istr + "/delta_file";
        std::string newFileName = "test_cases/t" + istr + "/new_file" + extension;

        constexpr int paramcount = 5;
        const char *argv[paramcount] = {"rdiff", "delta", sigFileName.c_str(), newFileName.c_str(), deltaFileName.c_str()};
        p = std::make_unique<Parameters>(paramcount, argv);

        rdiff = RdiffBuilder::build(std::move(p));
        rdiff->execute();
    } catch(std::runtime_error& r) {
        std::cout << r.what() << "\n";
        std::cout << "Test folder: t" << std::to_string(folderIndex) << "\n";
        throw;
    }

    void generatePatch(int folderIndex) try {
        std::string istr = std::to_string(folderIndex);
        std::string extension;
        if(folderIndex < binaryTestStarts) extension = ".txt";
        std::string deltaFileName = "test_cases/t" + istr + "/delta_file";
        std::string baseFileName = "test_cases/t" + istr + "/base_file" + extension;
        std::string patchedFileName = "test_cases/t" + istr + "/patched_file" + extension;

        constexpr int paramcount = 5;
        const char *argv[paramcount] = {"rdiff", "patch", baseFileName.c_str(), deltaFileName.c_str(), patchedFileName.c_str()};
        p = std::make_unique<Parameters>(paramcount, argv);

        rdiff = RdiffBuilder::build(std::move(p));
        rdiff->execute();
    } catch(std::runtime_error& r) {
        std::cout << r.what() << "\n";
        std::cout << "Test folder: t" << std::to_string(folderIndex) << "\n";
        throw;
    }
}

TEST(Rdiff, Init_1) {
    for(int i = 0; i < folderCount; ++i) {
        std::string istr = std::to_string(i);
        std::string extension;
        if(i < binaryTestStarts) extension = ".txt";
        std::string command = "rm -f test_cases/t" + istr + "/sig_file test_cases/t" + istr + "/delta_file test_cases/t" + istr +
                "/patched_file" + extension;
        ASSERT_EQ(system(command.c_str()), 0) << "ERROR: rm sig_file/delta_file/patched_file failed in test_cases/t" << i << " folder";
    }
}

TEST(Rdiff, T_signature_h1) {
    hashFunction = "1";
    for(int i = 0; i < folderCount; ++i) {
        ASSERT_NO_THROW(generateSignature(i));
        std::string signatureFileName = "test_cases/t" + std::to_string(i) + "/sig_file";
        std::ifstream signatureFile(signatureFileName, std::ios::in);
        ASSERT_TRUE(signatureFile.is_open()) << "ERROR: signature file error in test_cases/t" << i << " folder";
        signatureFile.close();
    }
}

TEST(Rdiff, T_delta_h1) {
    for(int i = 0; i < folderCount; ++i) {
        ASSERT_NO_THROW(generateDelta(i));
        std::string deltaFileName = "test_cases/t" + std::to_string(i) + "/delta_file";
        std::ifstream deltaFile(deltaFileName.c_str(), std::ios::in);
        ASSERT_TRUE(deltaFile.is_open()) << "ERROR: delta file error in test_cases/t" << i << " folder";
    }
}

TEST(Rdiff, T_patch_h1) {
    for(int i = 0; i < folderCount; ++i) {
        ASSERT_NO_THROW(generatePatch(i));
        if(i >= binaryTestStarts) {
            // binary diff tests
            std::string command = "md5sum --status -c ./test_cases/t" + std::to_string(i) + "/checklist >/dev/null";
            ASSERT_EQ(system(command.c_str()), 0) << "ERROR: Invalid result in test_cases/t" << i << " folder";
        } else {
            // text diff tests
            std::string command = "diff ./test_cases/t" + std::to_string(i) + "/patched_file.txt ./test_cases/t" +
                    std::to_string(i) + "/new_file.txt";
            ASSERT_EQ(system(command.c_str()), 0) << "ERROR: Invalid result in test_cases/t" << i << " folder\n";
        }
    }
}

TEST(Rdiff, Init_2) {
    for(int i = 0; i < folderCount; ++i) {
        std::string istr = std::to_string(i);
        std::string extension;
        if(i < binaryTestStarts) extension = ".txt";
        std::string command = "rm -f test_cases/t" + istr + "/sig_file test_cases/t" + istr + "/delta_file test_cases/t" + istr +
                "/patched_file" + extension;
        ASSERT_EQ(system(command.c_str()), 0) << "ERROR: rm sig_file/delta_file/patched_file failed in test_cases/t" << i << " folder";
    }
}


TEST(Rdiff, T_signature_h2) {
    hashFunction = "2";
    for(int i = 0; i < folderCount; ++i) {
        ASSERT_NO_THROW(generateSignature(i));
        std::string signatureFileName = "test_cases/t" + std::to_string(i) + "/sig_file";
        std::ifstream signatureFile(signatureFileName, std::ios::in);
        ASSERT_TRUE(signatureFile.is_open()) << "ERROR: signature file error in test_cases/t" << i << " folder";
        signatureFile.close();
    }
}

TEST(Rdiff, T_delta_h2) {
    for(int i = 0; i < folderCount; ++i) {
        ASSERT_NO_THROW(generateDelta(i));
        std::string deltaFileName = "test_cases/t" + std::to_string(i) + "/delta_file";
        std::ifstream deltaFile(deltaFileName.c_str(), std::ios::in);
        ASSERT_TRUE(deltaFile.is_open()) << "ERROR: delta file error in test_cases/t" << i << " folder";
    }
}

TEST(Rdiff, T_patch_h2) {
    for(int i = 0; i < folderCount; ++i) {
        ASSERT_NO_THROW(generatePatch(i));
        if(i >= binaryTestStarts) {
            // binary diff tests
            std::string command = "md5sum --status -c ./test_cases/t" + std::to_string(i) + "/checklist >/dev/null";
            ASSERT_EQ(system(command.c_str()), 0) << "ERROR: Invalid result in test_cases/t" << i << " folder";
        } else {
            // text diff tests
            std::string command = "diff ./test_cases/t" + std::to_string(i) + "/patched_file.txt ./test_cases/t" +
                    std::to_string(i) + "/new_file.txt";
            ASSERT_EQ(system(command.c_str()), 0) << "ERROR: Invalid result in test_cases/t" << i << " folder\n";
        }
    }
}
