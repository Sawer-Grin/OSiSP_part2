#include <iostream>
#include <windows.h>
#include "../Library/_library/library.cpp"

typedef BOOL (*ReplaceStringFunc)(DWORD pId,
                                  const char *stringToReplace,
                                  const char *replaceString);

static char secret[] = "HELLO WORLD!!!!!";
int aes = 4096;

PVOID AllocExample(){
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

    PVOID exPtr = AllocExample();

    if (replace_string_in_process(GetCurrentProcessId(), secret, "SUPER SECRET"))
    {
        std::cout << "Correct"<< std::endl;
    }
    else
    {
        std::cout << "Error while trying to replace string." << std::endl;
    }

    ReadAllocExample(exPtr);
    return 0;
}