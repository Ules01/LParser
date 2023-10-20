#!/bin/sh

if [ $# -ne 0 ]; then
  cd Cpp/src
  cmake CMakeLists.txt
  make
  echo $1
  ./draw $1

  rm graphivz/graph.dot
  ./draw $1 >> graphivz/graph.dot

  rm -rf CMakeFiles cmake_install.cmake Makefile draw CMakeCache.txt

  rm graphivz/graph.dot.png
  dot -Tpng -O graphivz/graph.dot &&  sxiv graphivz/graph.dot.png

fi