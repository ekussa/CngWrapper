#ifndef NTSTATUSHELPER_H
#define NTSTATUSHELPER_H

#include <Windows.h>
#include <bcrypt.h>
#include <string>

namespace CngWrapper
{

class NtStatusHelper
{
public:
    static bool isError(const NTSTATUS result);
    static bool isSuccess(const NTSTATUS result);

    static std::string toString(const NTSTATUS result);
    static std::wstring toWString(const NTSTATUS result);
};

}

#endif // NTSTATUSHELPER_H

