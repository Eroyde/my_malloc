cmake_minimum_required(VERSION 3.9)
project(my_malloc C)

set(CMAKE_C_STANDARD 99)

find_package (Threads)

add_library(my_malloc SHARED src/malloc.c src/malloc.h src/malloc.c src/malloc.h src/free.c src/block.c src/realloc.c src/calloc.c src/show_alloc_mem.c src/list_metadata.c src/list_metadata.c)

target_link_libraries (my_malloc ${CMAKE_THREAD_LIBS_INIT})
