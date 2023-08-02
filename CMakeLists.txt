cmake_minimum_required(VERSION 3.16)
project(c-example-mini)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_subdirectory(lib)

add_executable(c-example-mini src/main.c)
target_link_libraries(c-example-mini lib)
