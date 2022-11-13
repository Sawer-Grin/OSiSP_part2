#ifndef LAB3_LIBRARY_H
#define LAB3_LIBRARY_H

#include <iostream>
#include <windows.h>

#ifdef LAB3_LIBRARY_EXPORTS
#define LAB3_LIBRARY_API __declspec(dllexport)
#else
#define LAB3_LIBRARY_API __declspec(dllimport)
#endif

typedef struct ParametersForReplacing{
    char* find_string;
    char* new_string;
} ParametersForReplacing;

extern "C" LAB3_LIBRARY_API BOOL replace_string_in_process(DWORD pId, 
                                                            const char *string_for_replacing, 
                                                            const char *replaced_string);

extern "C" LAB3_LIBRARY_API BOOL replace_string_in_process_for_inj(ParametersForReplacing *param);


#endif //LAB3_LIBRARY_H