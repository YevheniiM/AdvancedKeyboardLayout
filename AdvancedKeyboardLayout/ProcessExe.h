#include <iostream>
#include <windows.h>
#include <Winuser.h>
#include <map>
#include <fstream>
#include <sstream>
#include <chrono>
#include <ctime>

using std::cout;
using std::cin;
using std::endl;
using std::string;

string read_exe(string prog, string arg)
{
    auto command = prog + " " + arg;

    BOOL ok = TRUE;
    HANDLE hStdInPipeRead = NULL;
    HANDLE hStdInPipeWrite = NULL;
    HANDLE hStdOutPipeRead = NULL;
    HANDLE hStdOutPipeWrite = NULL;

    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE };
    ok = CreatePipe(&hStdInPipeRead, &hStdInPipeWrite, &sa, 0);
    if (ok == FALSE) return "CreatePipe failed";
    ok = CreatePipe(&hStdOutPipeRead, &hStdOutPipeWrite, &sa, 0);
    if (ok == FALSE) return "CreatePipe failed";

    STARTUPINFO si = { };
    si.cb = sizeof(STARTUPINFO);
    si.dwFlags = STARTF_USESTDHANDLES;
    si.hStdError = hStdOutPipeWrite;
    si.hStdOutput = hStdOutPipeWrite;
    si.hStdInput = hStdInPipeRead;
    PROCESS_INFORMATION pi = { };

    TCHAR lpCommandLine[1024] = { 0 };
    mbstowcs(lpCommandLine, command.c_str(), 1024);

    LPSECURITY_ATTRIBUTES lpProcessAttributes = NULL;
    LPSECURITY_ATTRIBUTES lpThreadAttribute = NULL;
    BOOL bInheritHandles = TRUE;
    DWORD dwCreationFlags = 0;
    LPVOID lpEnvironment = NULL;
    LPCWSTR lpCurrentDirectory = NULL;

    ok = CreateProcess(
        NULL,
        lpCommandLine,
        lpProcessAttributes,
        lpThreadAttribute,
        bInheritHandles,
        dwCreationFlags,
        lpEnvironment,
        lpCurrentDirectory,
        &si,
        &pi);

    if (ok == FALSE) return "CreateProcess failed";

    CloseHandle(hStdOutPipeWrite);
    CloseHandle(hStdInPipeRead);

    char buf[1024 + 1] = { };
    DWORD dwRead = 0;
    DWORD dwAvail = 0;
    ok = ReadFile(hStdOutPipeRead, buf, 1024, &dwRead, NULL);
    string str{};
    while (ok == TRUE)
    {
        buf[dwRead] = '\0';
        OutputDebugStringA(buf);
        str += string{ buf };
        ok = ReadFile(hStdOutPipeRead, buf, 1024, &dwRead, NULL);
    }

    CloseHandle(hStdOutPipeRead);
    CloseHandle(hStdInPipeWrite);
    DWORD dwExitCode = 0;
    GetExitCodeProcess(pi.hProcess, &dwExitCode);
    return str;
}