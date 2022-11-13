#include <iostream>
#include <windows.h>

typedef BOOL (*ReplaceStringFunc)(DWORD pId,
                                  const char *stringToReplace,
                                  const char *replaceString);

char secret[] = "hello world";
int aes = 4096;

PVOID alloc_example(){
    PVOID pvMem = VirtualAlloc(NULL,aes , MEM_COMMIT, PAGE_READWRITE);
    memcpy(pvMem, secret, strlen(secret)+1);
    printf("Start: %s\n", pvMem);
    return pvMem;
}

void read_alloc_example(PVOID ptr){
    printf("End: %s\n", ptr);
}

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    PVOID attacked_string = alloc_example();
    std::cout << "Current pid: " << GetCurrentProcessId() << std::endl;
    getchar();
    system("clear");
    read_alloc_example(attacked_string);
    return 0;
}