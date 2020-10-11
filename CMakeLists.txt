cmake_minimum_required(VERSION 3.17)
project(AmongFile)

set(CMAKE_CXX_STANDARD 20)

add_executable(AmongFile main.cpp FileSearch.cpp Flags.cpp Parser.cpp)