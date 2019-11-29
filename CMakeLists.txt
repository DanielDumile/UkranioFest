cmake_minimum_required(VERSION 3.15)
project(UKfest)

set(CMAKE_CXX_STANDARD 11)

add_executable(sortDic sortDiccionario.cpp)

file(COPY diccionario.txt DESTINATION "${UKfest_BINARY_DIR}")
