#include <stdio.h>
#include <windows.h>

//------------------------ MAIN ------------------------------------------------
int main(int argc, char* argv[])
{
    auto hLibrary = LoadLibraryA("libcmake_example_3_lib.so");
    return 0;
}