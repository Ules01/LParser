cmake_minimum_required(VERSION 3.25)
project(LParser)

set(CMAKE_CXX_STANDARD 14)

include_directories(Cpp)

add_executable(
        testsuit
        Cpp/src/Token.hh
        Cpp/src/Graphe.hh
        Cpp/src/LParser.hh
        Cpp/src/Token.cc
        Cpp/src/Graphe.cc
        Cpp/src/LParser.cc
        Cpp/CTestSuitClass/testStruct.hh
        Cpp/CTestSuitClass/testStruct.cc
        Cpp/testsuit.cc
)
