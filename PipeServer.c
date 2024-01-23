#include <windows.h>
#include <stdio.h>

// Server

int main()
{
    printf("------- Server End --------\n");
    // NamedPipe Local Variable
    HANDLE pipe;
    char inputBuffer[1023];
    char outputBuffer[1023];
    DWORD dwinputBuffer = sizeof(inputBuffer);
    DWORD dwoutputBuffer = sizeof(outputBuffer);
    // Connection NamedPipe Local Variable
    BOOL bConnectNamedPipe;
    // WriteFile Local Variable
    BOOL bWriteFile;
    char WriteFileBuffer[1023] = "Hello From NamedPipe Server"; // 通过管道发送给客户端的消息
    DWORD dwWriteFileBuffer = sizeof(WriteFileBuffer);
    DWORD dwNoBytesWrite;
    BOOL bFlushFileBuffer;
    // ReadFile Local Variable
    BOOL bReadFile;
    char ReadFileBuffer[1023];
    DWORD dwReadFileBuffer = sizeof(ReadFileBuffer);
    DWORD dwNoBytesRead;
    // CreateNamedPipe - Step 1
    pipe = CreateNamedPipe(
        L"\\\\.\\pipe\\my_pipe",     // 命名管道名称
        PIPE_ACCESS_DUPLEX,         // 可读可写的管道
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, // 字节类型的管道
        PIPE_UNLIMITED_INSTANCES,   // 允许无限个实例
        dwoutputBuffer,                          // 输出缓冲区的大小
        dwinputBuffer,                          // 输入缓冲区的大小
        0,                          // 默认超时时间
        NULL                        // 默认安全属性
    );
    if (pipe == INVALID_HANDLE_VALUE) {
        printf("NamedPipe Creation Failed & Error No - ");
        printf("%d\n", GetLastError());
    }
    printf("NamedPipe Creation Success\n");

    // Connect Pipe - Step 2
    BOOL connected = ConnectNamedPipe(pipe, NULL);
    if (!connected) {
        printf("Failed to connect named pipe. & Error No - ");
        printf("%d\n", GetLastError());
    }
    printf("NamedPipe Connection Success\n");

    // Write File - Step 3
    bWriteFile = WriteFile(pipe, WriteFileBuffer, dwWriteFileBuffer, &dwNoBytesWrite, NULL);
    if (bWriteFile == FALSE) {
        printf("Read Failed = ");
        printf("%d\n", GetLastError());
    }

    // Flush File Buffer -Step 4
    bFlushFileBuffer = FlushFileBuffers(pipe);
    if (bFlushFileBuffer == FALSE) {
        printf("FlushFileBuffer Failed = ");
        printf("%d\n", GetLastError());
    }
    printf("Flush File Buffer Success\n");
    // Read File Buffer -Step 5
    bReadFile = ReadFile(pipe, ReadFileBuffer, dwReadFileBuffer, &dwNoBytesRead, NULL);
    if (bReadFile == FALSE) {
        printf("ReadFile Failed = ");
        printf("%d\n", GetLastError());
    }
    printf("ReadFile Success\n");

    printf("Data Reading From Client -> %s\n", ReadFileBuffer);
    // Disconnect
    DisconnectNamedPipe(pipe);

    // Close Handle
    CloseHandle(pipe);
    system("PAUSE");
    return 0;
}