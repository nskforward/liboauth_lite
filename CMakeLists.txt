cmake_minimum_required(VERSION 3.9)
project(liboauth C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_CFLAGS -m32)

#link_libraries(ssl)
#link_libraries(crypto)

add_library(oauth_lite SHARED src/xmalloc.c)
add_executable(test_liboath main.c src/oauth.c src/sha1.c src/memxor.c src/base64.c src/xmalloc.c)
