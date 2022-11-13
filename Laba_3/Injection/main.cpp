#include <windows.h>
#include <iostream>
#include <string>
#include <tlhelp32.h>

#define benefits_from_wine 0x0000000300000000

std::string initial_string = std::string("hello world");
std::string new_string = std::string("password");
std::string custom_dll = std::string("lib_virtual_memory_shared.so");

int aes = 4096;

typedef struct ParametersForReplacing{
    char* find_string;
    char* new_string;
} ParametersForReplacing;

DWORD get_process_id(char *process_name) {
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (Process32First(snapshot, &entry) == TRUE)
    {
        while (Process32Next(snapshot, &entry) == TRUE)
        {
            if (!strcmp(entry.szExeFile, process_name))
            {  
                CloseHandle(snapshot);
                return entry.th32ProcessID;
            }
        }
    }

    CloseHandle(snapshot);
    return 0;
}

int inject_dll(HANDLE process, std::string& dll_name, std::string& string_for_finding, std::string& string_for_replacing){

    size_t size_dll_name = custom_dll.length() + 1, size_of_init_string = string_for_finding.length() + 1, 
        size_for_rep_string = string_for_replacing.length() + 1, 
        size_for_strings = size_dll_name + size_of_init_string + size_for_rep_string;

    char *buffer = (char *) malloc(sizeof(char) * (size_for_strings));
    if (buffer == NULL) {
        std::cerr << "Problem with malloc: " << std::endl;
        free(buffer);
        exit(1);
    }
    strcpy(buffer, custom_dll.c_str());
    strcpy(buffer + size_dll_name, string_for_finding.c_str());
    strcpy(buffer + size_dll_name + size_of_init_string, string_for_replacing.c_str());

    LPVOID alloc_for_string = VirtualAllocEx(process, NULL, size_for_strings, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
    if (alloc_for_string == NULL){
        CloseHandle(process);
        std::cerr << "Problem with virtual alloc1" << std::endl;
        exit(1);
    }

    SIZE_T bytes_written = 0;
    HANDLE handle_thread;
    DWORD h_module = 0;

    int result_of_writing = WriteProcessMemory(process, alloc_for_string, buffer, size_for_strings, &bytes_written);
    if (result_of_writing){

        FARPROC loadLibraryPointer = GetProcAddress(GetModuleHandle("kernel32.dll"), "LoadLibraryA");
        if (loadLibraryPointer == NULL){
            printf("Can't get pointer on LoadLibraryA!");
            exit(1);
        }
        handle_thread = CreateRemoteThread(process, NULL, 0, 
            (LPTHREAD_START_ROUTINE)loadLibraryPointer,
            alloc_for_string, 0, NULL);

        if (handle_thread == NULL) {
            CloseHandle(handle_thread);
            std::cerr << "Problem with first creating a thread" << std::endl;
            exit(1);
        }

        WaitForSingleObject(handle_thread, INFINITE);
        DWORD threadID = GetExitCodeThread(handle_thread, &h_module);
        std::cout << "Module handle in remote process: " << std::hex << (unsigned long long)h_module << std::endl;
        CloseHandle(handle_thread);

    } else {
        CloseHandle(process);
        std::cerr << "Problem with writing data form buffer to virtual memory" << std::endl;
        exit(1);
    }

    ParametersForReplacing args = {
        .find_string = (char *)alloc_for_string + size_dll_name,
        .new_string = (char *)alloc_for_string + size_dll_name + size_of_init_string,
    };

    LPVOID args_address = VirtualAllocEx(process, NULL, sizeof(&args), MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
    if (args_address == NULL) {
        std::cerr << "Problem with VirtualAllocEx for args" << std::endl;
        VirtualFreeEx(process, NULL, 0, MEM_RELEASE);
        CloseHandle(process);
        exit(1);
    }

    result_of_writing = WriteProcessMemory(process, args_address, &args, sizeof(args), &bytes_written);
    if (result_of_writing == 0){
        std::cerr << "Can't write in virtual memory args" << std::endl;
        VirtualFreeEx(process, NULL, 0, MEM_RELEASE);
        CloseHandle(process);
        exit(1);
    }

    HINSTANCE library = LoadLibraryA(custom_dll.c_str());
    if (library == NULL) {
        std::cout << "Error loading" << std::endl;
    }

    FARPROC replacer_string = (FARPROC) ((unsigned long long) GetProcAddress(GetModuleHandle(custom_dll.c_str()), "replace_string_in_process_for_inj") - (unsigned long long) library + h_module + benefits_from_wine);
    std::cout << "Replacer string: " << (long long)replacer_string << std::endl;
    handle_thread = CreateRemoteThread(process, NULL, 0, (LPTHREAD_START_ROUTINE) replacer_string, args_address, 0, NULL);
    FreeLibrary(library);
    if (handle_thread == NULL) {
        std::cerr << "Problem with creating remote thread" << std::endl;
        VirtualFreeEx(process, NULL, 0, MEM_RELEASE);
        CloseHandle(process);
        exit(1);
    }

    WaitForSingleObject(handle_thread, INFINITE);
    CloseHandle(handle_thread);

    VirtualFreeEx(process, alloc_for_string, 0, MEM_RELEASE);
    VirtualFreeEx(process, args_address, 0, MEM_RELEASE);
    CloseHandle(process);

    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    char pName[] = "main.exe";
    DWORD pid = 0;
    pid = get_process_id(pName);
    std::cout << "Pid: " << pid << std::endl;
    
    HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
    if (process == NULL) {
        std::cerr << "Can't open process" << std::endl;
        exit(1);
    }

    return inject_dll(process, custom_dll, initial_string, new_string);
}