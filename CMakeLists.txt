cmake_minimum_required(VERSION 3.30)
project(UTP1)

set(CMAKE_CXX_STANDARD 20)

add_library(UTP1 SHARED Game.h
        Game.cpp
        JUtils.h)

target_include_directories(UTP1 PRIVATE /home/yudek/.jdks/openjdk-23.0.1/include)

target_include_directories(UTP1 PRIVATE /home/yudek/.jdks/openjdk-23.0.1/include/linux)