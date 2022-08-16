#include <gtest/gtest.h>

int main(int argc, char *argv[]) {
    testing::InitGoogleTest(&argc, (char**)argv);
    //testing::GTEST_FLAG(filter)="FastFileOutput.*";
    return RUN_ALL_TESTS();
}
