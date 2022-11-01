#!/bin/bash

$1=$(x86_64-w64-mingw32-g++ main.cpp -o  main -L /usr/x86_64-w64-mingw32/sys-root/mingw/lib/ -static-libstdc++)

WINEPATH=/usr/x86_64-w64-mingw32/sys-root/mingw/bin/ wine ./main.exe --help