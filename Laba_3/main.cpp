#include <windows.h>
#include <iostream>

#define amount_in_line 4
#define amount_in_column 5
#define default_height_line_text 20

std::string test_string = std::string("Hello, world");

const char g_szClassName[] = "myWindowClass";
int size_width = 500;
int size_height = 500;

bool replace_string_in_process(DWORD pId, const char *string_for_replacing, const char *replaced_string) {

    if (string_for_replacing == nullptr || replaced_string == nullptr) {
        return false;
    }

    char *str = new char[strlen(string_for_replacing) + 1];
    strcpy_s(str, strlen(string_for_replacing) + 1, string_for_replacing);
    SYSTEM_INFO si;

    GetSystemInfo(&si);

    DWORD old_pid = GetCurrentProcessId();

    HANDLE hProcess = OpenProcess(
        PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_VM_WRITE,
        false,
        pId
    );

    DWORD new_pid = GetProcessId(hProcess);
    DWORD new_old_pid = GetCurrentProcessId();

    std::cout << "Old pid: " << old_pid 
        << " OpenProcessId: " << new_pid 
        << " After open proccess: " << new_old_pid << std::endl;

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
                    LPVOID str_address = (LPVOID)((BYTE*) mbi
                        .BaseAddress+ i);
                    std::cout << "Str: " << (char *) str_address << std::endl;

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
                        std::cout << "Successful result of changing string!!!!!!!" << std::endl;
                        std::cout << "Shit == " << test_string << "But == "  << (char*)str_address << std::endl;
                    }
                }
            }
        }
        delete[] buf;
    }
    delete[] str;

    return true;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    static HWND hwndListView;
    static int inputReady = true;
    switch(msg)
    {
        case WM_CREATE:{
            std::cout << "Start checking Shit" << std::endl;
            DWORD own_pid = GetCurrentProcessId();

            replace_string_in_process(own_pid, "Hello, world", "Something");
            break;
        }
        case WM_SIZE:{
            break;
        }
        case WM_COMMAND:{
            break;
        }
        case WM_GETMINMAXINFO:
        {
            break;
        }
        case WM_VSCROLL: {
            break;
        }
        case WM_CLOSE:
            std::cout << 
            DestroyWindow(hwnd);
        break;
        case WM_DESTROY:
            PostQuitMessage(0);
        break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc;
    HWND hwnd;
    MSG Msg;

    /// Initialise the main settings 

    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
    wc.lpszMenuName  = NULL;
    wc.lpszClassName = g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        g_szClassName,
        "Laba_3",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, size_width, size_height,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}