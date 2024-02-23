#!/bin/bash

# 0. crear fuente y CMakeLists.txt
# 1. mkdir build
# 2. cd build
# 3. cmake ..  (le decimos a cmake donde está el CMakeLists.txt
# 4. cmake --build . (equivalente a hacer un make)
# 5. ./Executable

mkdir build 2> /dev/null
cd build
cmake ..
cmake --build .
