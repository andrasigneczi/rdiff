#include <gtest/gtest.h>
#include "FastFileInput.h"
#include "FastFileOutput.h"

namespace {
    InputInterfaceUPtr fastFileInput;
    OutputInterfaceUPtr fastFileOutput;
}

TEST(FastFileOutput, Init) {
    fastFileInput = InputInterfaceUPtr(new FastFileInput("test_cases/t10/base_file"));
    ASSERT_TRUE(fastFileInput->open());
    fastFileOutput = OutputInterfaceUPtr(new FastFileOutput("test_cases/t10/base_file_copy"));
    ASSERT_TRUE(fastFileOutput->open());
}

TEST(FastFileOutput, Copy) {
    std::vector<uint8_t> buffer;

    for(int i = 0; i < 76418; ++i) {
        ASSERT_TRUE(fastFileInput->get(buffer, 90));
        ASSERT_EQ(buffer.size(), 90);
        fastFileOutput->put(buffer, 90);
    }

    for(int i = 0; i < 52; ++i) {
        ASSERT_TRUE(fastFileInput->get(buffer, 1));
        fastFileOutput->put(buffer, 1);
    }

    fastFileOutput->flush();
    fastFileOutput->close();
    fastFileInput->close();
}

TEST(FastFileOutput, Test) {
    std::string command = "md5sum --status -c ./test_cases/t10/copy_output.txt >/dev/null";
    ASSERT_EQ(system(command.c_str()), 0) << "ERROR: Invalid result in test_cases/t10 folder";
}

TEST(FastFileOutput, CleanUp) {
    ASSERT_EQ(system("rm -f test_cases/t10/base_file_copy"), 0);
}
