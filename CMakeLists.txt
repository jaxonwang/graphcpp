cmake_minimum_required(VERSION 3.10)

# set the project name
project(Graph VERSION 0.1)

# add the executable
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wno-long-long -pedantic")

find_package(Boost REQUIRED)

include_directories(${Boost_INCLUDE_DIRS})

add_executable(graph test.cc)

add_executable(fpbymeta fpcpp.cc)

