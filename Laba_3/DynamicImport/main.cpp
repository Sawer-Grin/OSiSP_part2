#include <iostream>
#include <windows.h>

typedef BOOL (*ReplaceStringFunc)(DWORD pId,
                                  const char *stringToReplace,
                                  const char *replaceString);

static char secret[] = "HELLO WORLD!!!!!";
int aes = 4096;

PVOID alloc_example(){
    PVOID pvMem = VirtualAlloc(NULL,aes , MEM_COMMIT, PAGE_READWRITE);
    memcpy(pvMem, secret, strlen(secret)+1);
    printf("Start: %s\n", pvMem);
    return pvMem;
}

void ReadAllocExample(PVOID ptr){
    printf("End: %s\n", ptr);
}

int main()
{
    PVOID exPtr = alloc_example();
    std::cout << "Here"<< std::endl;
    auto hLibrary = LoadLibraryA("lib_virtual_memory_shared.so");

    if (hLibrary == nullptr)
    {
        std::cout << "Could not load library." << std::endl;
        return 1;
    }

    auto func = (ReplaceStringFunc) GetProcAddress(hLibrary,
                                                   "replace_string_in_process");

    if (func != nullptr)
    {
        if (func(GetCurrentProcessId(), secret, "SUPER SECRET"))
        {
            std::cout << "Correct"<< std::endl;
        }
        else
        {
            std::cout << "Error while trying to replace string." << std::endl;
        }
    }
    else
    {
        std::cout << "Could not find function with name 'ReplaceStringInProcess'"
             << std::endl;
    }

    ReadAllocExample(exPtr);

    FreeModule(hLibrary);

    return 0;
}