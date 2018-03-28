cmake_minimum_required(VERSION 3.9)
project(liboauth C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_CFLAGS -m32)

add_library(oauth SHARED src/library.c src/library.h)
add_executable(test_liboath main.c)