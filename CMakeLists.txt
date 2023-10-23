cmake_minimum_required(VERSION 3.25)
project(crypting_machine)

set(CMAKE_CXX_STANDARD 20)

add_executable(crypting_machine main.cpp password.cpp password.h options.cpp options.h crypting.cpp crypting.h fileHandler.h)
