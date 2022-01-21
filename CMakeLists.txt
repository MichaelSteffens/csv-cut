#
# Copyright (C) 2022 Dr. Michael Steffens
#
# SPDX-License-Identifier:      BSL-1.0
#

cmake_minimum_required(VERSION 3.13)
project(csv-cut VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS NO)

find_package(Threads REQUIRED)  

add_executable(csv-cut src/csv-cut.cpp)
target_include_directories(csv-cut PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_link_libraries(csv-cut Threads::Threads)
