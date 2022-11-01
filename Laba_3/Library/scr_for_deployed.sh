#!/bin/bash

cd _library
rm -f -r build
mkdir build
cd build
cmake .. >/dev/null # if it not needed, you can delete
make #>/dev/null  because pretty output(with colors)

shared_lib=./lib_virtual_memory_shared.so
static_lib=./lib_virtual_memory_static.a

if [ -f "$shared_lib" ]; then
    if [ -f "$static_lib" ]; then
        cp $shared_lib ../../../complete_lib/
        cp $static_lib ../../../complete_lib/
        echo "....Successfully copied fiels....."
    else 
        echo ".....problem with file: $static_lib ..........."
    fi
else
     echo ".....problem with file: $shared_lib ..........."
fi