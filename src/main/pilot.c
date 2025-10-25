#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

extern volatile const char katana[];

void TerminateByID(DWORD process_id);
void TerminateByName(char *process_name);

char *usage = "ss.exe <process-id>\n\
                ss.exe -n <process-name>";

int main(int argc, char *argv[])
{
        DWORD id;
        
        katana;
        if (argc == 2) {
                if ((id = atoi(argv[1])) == 0) {
                        fprintf(stderr, "%s\n", usage);
                        return EXIT_FAILURE;
                }
                TerminateByID(id);
        } else if (argc == 3) {
                if (strcmp(argv[1], "-n") == 0) {
                        TerminateByName(argv[2]);
                } else {
                        fprintf(stderr, "%s\n", usage);
                        return EXIT_FAILURE;
                }
        } else {
                fprintf(stderr, "%s\n", usage);
                return EXIT_FAILURE;
        }
        return EXIT_SUCCESS;
}

void TerminateByID(DWORD id)
{
        HANDLE process;
        char process_name[120];
        DWORD pnamesiz = sizeof(process_name);
        
        if ((process = OpenProcess(PROCESS_TERMINATE | PROCESS_QUERY_LIMITED_INFORMATION, FALSE, id)) == NULL) {
                fprintf(stderr, "%s\n", "error opening process");
                return;
        }
        if (!QueryFullProcessImageName(
                                        process,
                                        0,
                                        process_name,
                                        &pnamesiz
        )) {
                fprintf(stderr, "%s %d\n", "error parsing process image name", GetLastError());
                return;
        }
        if (!TerminateProcess(process, 0)) {
                fprintf(stderr, "Error terminating Process #%d:\n%s\n", id, process_name);
                return;
        }
        CloseHandle(process);
        printf("Successfully terminated Process #%d:\n%s\n", id, process_name);
        return;
}

void TerminateByName(char *name)
{
        return;
}