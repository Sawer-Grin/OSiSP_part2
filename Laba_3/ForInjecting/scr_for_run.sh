#!/bin/bash

cp ../complete_lib/lib_virtual_memory_shared.so ./build
WINEPATH=/usr/x86_64-w64-mingw32/sys-root/mingw/bin/ wine ./build/main.exe --help
