cmake_minimum_required(VERSION 3.18)
project(CinemaCpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(CinemaCpp main.cpp Welcome.cpp "Basic Information.h" "Audience Info.h" "Admin Info.h" Arrangements.hpp)
