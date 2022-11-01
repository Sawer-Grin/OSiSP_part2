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

add_library(_virtual_memory Static library.hpp)
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
# target_link_libraries(DynamicLibrary -lcomctl32)
