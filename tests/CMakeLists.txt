cmake_minimum_required(VERSION 3.4.1)
project(rdiff)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_COMPILER "clang++-10")
#set(CMAKE_CXX_COMPILER "g++-10")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -O3 -pedantic -Wall -Wextra -Werror -Wno-unused-function -Wconversion -fPIC")

# Locate GTest
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} . ../src ../src//IO ../src/Interfaces)

add_executable(runTests main.cpp parameters.cpp fast_file_input.cpp fast_file_output.cpp polynomial_rhash.cpp cyclic_polinomial_rhash.cpp rdiff.cpp rdiff_app.cpp)
target_link_libraries(runTests ${GTEST_LIBRARIES} pthread Rdiff)
