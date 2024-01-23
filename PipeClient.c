#include <windows.h>
#include <stdio.h>
int main()
{
    printf("------- Client End --------\n");
    HANDLE hCreateFile;
    BOOL bReadFile;
    char ReadFileBuffer[1023];
    DWORD dwReadFileBuffer = sizeof(ReadFileBuffer);
    DWORD dwNoBytesRead;

    BOOL bWriteFile;
    char WriteFileBuffer[1023] = "Hello From NamedPipe Client"; // 通过管道返回给服务端的消息
    DWORD dwWriteFileBuffer = sizeof(WriteFileBuffer);
    DWORD dwNoBytesWrite;
    BOOL bFlushFileBuffer;

    hCreateFile = CreateFile(
        L"\\\\.\\pipe\\my_pipe",
        GENERIC_READ | GENERIC_WRITE,
        0,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    if (hCreateFile == INVALID_HANDLE_VALUE) {
        printf("File Creation Failed & Error No - ");
        printf("%d\n", GetLastError());
    }
    printf("File Creation Success\n");
    bReadFile = ReadFile(hCreateFile, ReadFileBuffer, dwReadFileBuffer, &dwNoBytesRead, NULL);
    if (bReadFile == FALSE) {
        printf("ReadFile Failed = ");
        printf("%d\n", GetLastError());
    }
    printf("ReadFile Success\n");
    printf("Data Reading From Server -> %s\n", ReadFileBuffer);
 

    bWriteFile = WriteFile(hCreateFile, WriteFileBuffer, dwWriteFileBuffer, &dwNoBytesWrite, NULL);
    if (bWriteFile == FALSE) {
        printf("WriteFile Failed = ");
        printf("%d\n", GetLastError());
    }
    printf("WriteFile Success\n");

    CloseHandle(hCreateFile);
    system("PAUSE");
    return 0;
}

