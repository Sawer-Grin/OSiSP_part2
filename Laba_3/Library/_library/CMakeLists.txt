cmake_minimum_required(VERSION 3.0.0)
project(_virtual_memory VERSION 0.1.0)

# setting for wine
set(CMAKE_CXX_COMPILER "/usr/bin/x86_64-w64-mingw32-g++")
set(CMAKE_C_COMPILER "/usr/bin/x86_64-w64-mingw32-gcc")
include_directories("/usr/x86_64-w64-mingw32/sys-root/mingw/include/")
link_directories("/usr/x86_64-w64-mingw32/sys-root/mingw/lib/")


set(CMAKE_SHARED_LIBRARY_LINK_C_FLAGS "")
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
set(CXX_COVERAGE_LINK_FLAGS "")
include(CTest)
enable_testing()

add_library(_virtual_memory OBJECT library.cpp)
target_include_directories(_virtual_memory PUBLIC)

add_library(_virtual_memory_static STATIC)
target_link_libraries(_virtual_memory_static PUBLIC _virtual_memory)

add_library(_virtual_memory_shared SHARED)
target_link_libraries(_virtual_memory_shared PUBLIC _virtual_memory)
