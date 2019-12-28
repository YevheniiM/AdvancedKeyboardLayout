cmake_minimum_required(VERSION 3.13)
project(linux)

set(CMAKE_CXX_STANDARD 14)

add_executable(remapper linux.cpp remapper.hpp)
