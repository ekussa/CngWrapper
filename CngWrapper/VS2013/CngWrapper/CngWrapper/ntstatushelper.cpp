#include "ntstatushelper.h"

namespace CngWrapper
{

static void* ntDllhandle = nullptr;

bool NtStatusHelper::isError(const NTSTATUS result)
{
    return result < 0;
}

bool NtStatusHelper::isSuccess(const NTSTATUS result)
{
    return !isError(result);
}

std::string NtStatusHelper::toString(const NTSTATUS result)
{
    if(!ntDllhandle)
        ntDllhandle = LoadLibrary(TEXT("NTDLL.DLL"));

    char* messageBuffer;
    FormatMessageA(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_FROM_HMODULE,
        ntDllhandle,
        result,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPSTR)&messageBuffer,
        0,
        nullptr);

    std::string ret(messageBuffer);

    LocalFree(messageBuffer);

    return ret;
}

std::wstring NtStatusHelper::toWString(const NTSTATUS result)
{
    if(!ntDllhandle)
        ntDllhandle = LoadLibrary(TEXT("NTDLL.DLL"));

    wchar_t* messageBuffer;
    FormatMessageW(
        FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_FROM_HMODULE,
        ntDllhandle,
        result,
        MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
        (LPWSTR)&messageBuffer,
        0,
        nullptr);

    std::wstring ret(messageBuffer);

    LocalFree(messageBuffer);

    return ret;
}

}
