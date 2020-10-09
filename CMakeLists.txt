cmake_minimum_required(VERSION 3.17)
project(FileSearcher)

set(CMAKE_CXX_STANDARD 20)

add_executable(FileSearcher main.cpp FileSearch.cpp Flags.cpp Parser.cpp)