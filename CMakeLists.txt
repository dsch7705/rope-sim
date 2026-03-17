cmake_minimum_required(VERSION 3.30)
project(rope-sim LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(extern)
add_subdirectory(src)