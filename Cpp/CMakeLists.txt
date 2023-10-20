cmake_minimum_required(VERSION 3.25)
project(LParser)

set(CMAKE_CXX_STANDARD 14)

include_directories(Cpp)

add_executable(
        testsuit
        src/Token.hh
        src/Graphe.hh
        src/LParser.hh
        src/Token.cc
        src/Graphe.cc
        src/LParser.cc
        CTestSuitClass/testStruct.hh
        CTestSuitClass/testStruct.cc
        testsuit.cc
)
