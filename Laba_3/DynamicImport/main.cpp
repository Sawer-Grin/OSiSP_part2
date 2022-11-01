#include <iostream>
#include <windows.h>

typedef BOOL (*ReplaceStringFunc)(DWORD pId,
                                  const char *stringToReplace,
                                  const char *replaceString);

using namespace std;

static char secret[] = "HELLO WORLD!!!!!";

int main()
{
    auto hLibrary = LoadLibraryA("lib_virtual_memory_shared.so");

    if (hLibrary == nullptr)
    {
        cout << "Could not load library." << endl;
        return 1;
    }

    auto func = (ReplaceStringFunc) GetProcAddress(hLibrary,
                                                   "replace_string_in_process");

    if (func != nullptr)
    {
        if (func(GetCurrentProcessId(), "HELLO WORLD!!!!!", "SUPER SECRET"))
        {
            cout << "Let's print string 'secret': " << secret << endl;
        }
        else
        {
            cout << "Error while trying to replace string." << endl;
        }
    }
    else
    {
        cout << "Could not find function with name 'ReplaceStringInProcess'"
             << endl;
    }

    FreeModule(hLibrary);

    return 0;
}