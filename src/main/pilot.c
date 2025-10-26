#include "ss.h"
#include <stdio.h>
#include <stdlib.h>

#define MODPATH         "ntdll.dll"
#define PROCEDURE       "NtTerminateProcess"
#define EXITCODE        77

int main(int argc, char *argv[])
{
        HMODULE dll;
        HANDLE file;
        int process_id;
        __ntterminateprocess call;
        char *usage = "ss.exe <process-id>";
        
        if (argc != 2) {
                fprintf(stderr, "%s\n", usage);
                return EXIT_FAILURE;
        }
        if ((process_id = atoi(argv[1])) == 0) {
                fprintf(stderr, "%s\n", usage);
                return EXIT_FAILURE;
        }
        if ((dll = GetModuleHandle(MODPATH)) == NULL)
                if ((dll = LoadLibrary(MODPATH)) == NULL) {
                        fprintf(stderr, "%s\n", "Unable to load dll");
                        return EXIT_FAILURE;
                }
        if ((call = (__ntterminateprocess) GetProcAddress(dll, PROCEDURE)) == NULL) {
                fprintf(stderr, "%s\n", "Unable to get an address for the procedure");
                return EXIT_FAILURE;
        }
        if ((file = OpenProcess(PROCESS_TERMINATE, FALSE, process_id)) == NULL) {
                fprintf(stderr, "%s\n", "Unable to open target process");
                return EXIT_FAILURE;
        }
        if (call(file, EXITCODE) != 0) {
                fprintf(stderr, "%s\n", "Failed to terminate target process");
                return EXIT_FAILURE;
        }
        printf("%s\n", "Successfully terminated target process");
        CloseHandle(file);
        FreeLibrary(dll);
        return EXIT_SUCCESS;
}