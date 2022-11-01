#define LAB3_LIBRARY_EXPORTS

#include "library.hpp"

BOOL replace_string_in_process(DWORD pId, const char *string_for_replacing, const char *replaced_string) {

    if (string_for_replacing == nullptr || replaced_string == nullptr) {
        return false;
    }

    char *str = new char[strlen(string_for_replacing) + 1];
    strcpy_s(str, strlen(string_for_replacing) + 1, string_for_replacing);
    SYSTEM_INFO si;

    GetSystemInfo(&si);

    HANDLE hProcess = OpenProcess(
        PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE,
        false,
        pId
    );

    if (hProcess == nullptr) 
        return false;
    
    MEMORY_BASIC_INFORMATION mbi = {};

    while (true) {
        DWORD_PTR address = ((DWORD_PTR) mbi.BaseAddress + mbi.RegionSize);
        VirtualQueryEx(hProcess, (void *) address, &mbi, sizeof(mbi));

        if (!(mbi.Protect & (PAGE_READONLY | PAGE_READWRITE))){
            if (address > (DWORD_PTR) si.lpMaximumApplicationAddress)
                break;
            continue;
        }

        BYTE *buf = new BYTE[mbi.RegionSize];
        SIZE_T nBytes;

        if (ReadProcessMemory(hProcess, mbi.BaseAddress, buf, mbi.RegionSize, &nBytes)) {

            for (size_t i = 0; i < nBytes - strlen(str); i++) {
                if (
                    (((BYTE*) mbi.AllocationBase + i) != (BYTE*)str) && 
                    !memcmp((CHAR *) buf + i, str, strlen(str))
                ) {
                    LPVOID str_address = (LPVOID)((BYTE*) mbi.BaseAddress + i);
                    std::cout << "Str: " << replaced_string << std::endl;

                    if (!WriteProcessMemory(hProcess, str_address, replaced_string, 
                        strlen(replaced_string) + 1, nullptr)) {
                    
                        DWORD errorCode = GetLastError();
                        wchar_t sError[1024];
                        FormatMessageW(
                            FORMAT_MESSAGE_FROM_SYSTEM,
                            nullptr,
                            errorCode,
                            MAKELANGID(
                                LANG_ENGLISH,
                                SUBLANG_ENGLISH_US
                            ),
                            sError,
                            sizeof(sError) / sizeof(wchar_t),
                            nullptr
                        );
                    }
                    else {
                        std::cout << "Successful result of changing string!!!!!!!" << std::endl;                    }
                }
            }
        }
        delete[] buf;
    }
    delete[] str;

    return true;
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL,  // handle to DLL module
                    DWORD fdwReason,     // reason for calling function
                    LPVOID lpReserved)  // reserved
{
    return TRUE;  // Successful DLL_PROCESS_ATTACH.
}