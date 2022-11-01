#define LAB3_LIBRARY_EXPORTS

#include "sLibrary.hpp"

BOOL ReplaceStringInProcess(DWORD pId,
                            const char *stringToReplace,
                            const char *replaceString)
{
    if (stringToReplace == nullptr)
    {
        return FALSE;
    }

    if (replaceString == nullptr)
    {
        return FALSE;
    }

    char *str = new char[strlen(stringToReplace) + 1];
    strcpy_s(str, strlen(stringToReplace) + 1, stringToReplace);

    SYSTEM_INFO si;

    GetSystemInfo(&si);

    HANDLE hProcess = OpenProcess(
        PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE,
        false,
        pId);

    if (hProcess == nullptr)
    {
        return FALSE;
    }

    MEMORY_BASIC_INFORMATION mbi = {};
    //mbi.BaseAddress = (void *) 0x10000;

    while (true)
    {
        DWORD_PTR address = ((DWORD_PTR) mbi.BaseAddress + mbi.RegionSize);

        VirtualQueryEx(hProcess, (void *) address, &mbi, sizeof(mbi));

        if (!(mbi.Protect & (PAGE_READONLY | PAGE_READWRITE)))
        {
            //printf("[%.16llX]Protected!\n", address);
            if (address > (DWORD_PTR) si.lpMaximumApplicationAddress)
                break;
            continue;
        }

        BYTE *buf = new BYTE[mbi.RegionSize];
        SIZE_T nBytes;

        if (ReadProcessMemory(hProcess,
                              mbi.BaseAddress,
                              buf,
                              mbi.RegionSize,
                              &nBytes))
        {
            //printf("Read block with address [%.16lX]:\n", (DWORD_PTR)address);

            for (size_t i = 0; i < nBytes - strlen(str); i++)
            {
                if ((((BYTE*) mbi.AllocationBase + i) != (BYTE*) str) &&
                    !memcmp((CHAR *) buf + i, str, strlen(str)))
                {
                    //                    std::cout << "Address changed: " << std::hex << mbi.BaseAddress
                    //                              << std::dec << ". i = " << i << std::endl
                    //                              << "Str: " << std::hex << (LPVOID) str
                    //                              << std::endl;

                    LPVOID strAddress = (LPVOID)((BYTE*) mbi
                        .BaseAddress+ i);

                    if (!WriteProcessMemory(hProcess,
                                            strAddress,
                                            replaceString,
                                            strlen(replaceString) + 1,
                                            nullptr))
                    {
                        DWORD errorCode = GetLastError();
                        wchar_t sError[1024];
                        FormatMessageW(FORMAT_MESSAGE_FROM_SYSTEM,
                                       nullptr,
                                       errorCode,
                                       MAKELANGID(LANG_ENGLISH,
                                                  SUBLANG_ENGLISH_US),
                                       sError,
                                       sizeof(sError) / sizeof(wchar_t),
                                       nullptr);
                        //wprintf(L"[%.16lX] %s", strAddress, sError);
                    }
                    else
                    {
                        //wprintf(L"[%.16lX] String has changed.\n",
                        // strAddress);
                    }
                }
            }
        }

        delete[] buf;
    }
    delete[] str;

    return TRUE;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL,  // handle to DLL module
                    DWORD fdwReason,     // reason for calling function
                    LPVOID lpReserved)  // reserved
{
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}