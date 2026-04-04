// clang-format off
#include <windows.h>
#include <Lmcons.h>
// clang-format on
#include <chrono>
#include <system.h>

std::wstring getusername() {
    TCHAR username[UNLEN + 1]{};
    DWORD size = UNLEN + 1;
    GetUserName((TCHAR *)username, &size);

    std::wstring userstring = username;
    return userstring;
}

std::wstring gethostname() {
    TCHAR hostname[UNLEN + 1]{};
    DWORD size = UNLEN + 1;
    GetComputerName((TCHAR *)hostname, &size);

    std::wstring userhost = hostname;
    return userhost;
}

std::chrono::milliseconds getuptime() {
    auto uptime = std::chrono::milliseconds(GetTickCount64());
    return uptime;
}
