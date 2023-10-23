#!/bin/bash

if [ $# -ne 0 ]; then
  cd Cpp/src
  cmake CMakeLists.txt
  make
  for var in $*; do
    if [ $var = "-rebuild" ] || [ $var = "-rb" ]; then
      rm -rf CMakeFiles cmake_install.cmake Makefile draw CMakeCache.txt
      cmake CMakeLists.txt
      make
    elif [ $var = "clean" ]; then
        rm -rf CMakeFiles cmake_install.cmake Makefile draw CMakeCache.txt
    else
      rm graphivz/graph.dot
      rm graphivz/graph.dot.png
      ./draw $var >> graphivz/graph.dot
      dot -Tpng -O graphivz/graph.dot &&  sxiv graphivz/graph.dot.png
    fi
  done
else
  sxiv Cpp/src/graphivz/graph.dot.png
fi
