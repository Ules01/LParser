cmake_minimum_required(VERSION 3.25)
project(LParser)

set(CMAKE_CXX_STANDARD 14)

include_directories(Cpp)

add_executable(
        draw
        Token.hh
        Graphe.hh
        LParser.hh
        Token.cc
        Graphe.cc
        LParser.cc
        draw.cc
)