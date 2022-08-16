cmake_minimum_required(VERSION 3.4.1)
project(rdiff)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_COMPILER "clang++-10")
#set(CMAKE_CXX_COMPILER "g++-10")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20 -O3 -pedantic -Wall -Wextra -Werror -Wno-unused-function -Wconversion -fPIC -ffast-math")

include_directories(. ./IO ./Interfaces)

add_library(Rdiff SHARED
	    Rdiff.cpp
	    RdiffBuilder.cpp
	    Parameters.cpp
	    CyclicPolinomialRHash.cpp
	    CyclicPolinomialRHashStorage.cpp
	    IO/FileInput.cpp
	    IO/FastFileInput.cpp
	    IO/FileOutput.cpp
	    IO/FastFileOutput.cpp
	    IO/IOFactory.cpp
	    ClockReal.cpp
	    ClockFactory.cpp
	    CoutLogger.cpp
)

add_executable(rdiff main.cpp)
target_link_libraries(rdiff pthread Rdiff)
