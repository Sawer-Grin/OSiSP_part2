#ifndef LAB3_LIBRARY_H
#define LAB3_LIBRARY_H

#include <iostream>
#include <windows.h>

#ifdef LAB3_LIBRARY_EXPORTS
#define LAB3_LIBRARY_API __declspec(dllexport)
#else
#define LAB3_LIBRARY_API __declspec(dllimport)
#endif

extern "C" LAB3_LIBRARY_API BOOL ReplaceStringInProcess(DWORD pId,
                                                        const char *stringToReplace,
                                                        const char *replaceString);

#endif //LAB3_LIBRARY_H