#include "hash.h"

namespace CngWrapper
{

Hash::Hash(const std::wstring &algorithmName) :
    _algorithmHandle(nullptr),
    _hashHandle(nullptr),
    _algorithmName(algorithmName),
    _hash(),
    _hashObject()
{

}

Hash::~Hash()
{
    if(_hashHandle)
        BCryptDestroyHash(_hashHandle);

    if(_algorithmHandle)
        BCryptCloseAlgorithmProvider(_algorithmHandle, 0);
}

NTSTATUS Hash::initialize()
{
    auto result = BCryptOpenAlgorithmProvider(&_algorithmHandle, _algorithmName.c_str(), nullptr, 0);
    if (NtStatusHelper::isError(result)) return result;

    unsigned long reserved = 0, hashObjectSize = 0;
    result = BCryptGetProperty(_algorithmHandle, BCRYPT_OBJECT_LENGTH, reinterpret_cast<unsigned char*>(&hashObjectSize), sizeof(unsigned long), &reserved, 0);
    if (NtStatusHelper::isError(result)) return result;
    _hashObject.resize(hashObjectSize);

    unsigned long hashSize = 0;
    result = BCryptGetProperty(_algorithmHandle, BCRYPT_HASH_LENGTH, reinterpret_cast<unsigned char*>(&hashSize), sizeof(hashSize), &reserved, 0);
    if (NtStatusHelper::isError(result)) return result;
    _hash.resize(hashSize);

    return BCryptCreateHash(_algorithmHandle, &_hashHandle, _hashObject.data(), _hashObject.size(), nullptr, 0, 0);
}

NTSTATUS Hash::initialize(const size_t hashSize, const size_t hashObjectSize)
{
    auto result = BCryptOpenAlgorithmProvider(&_algorithmHandle, _algorithmName.c_str(), nullptr, 0);
    if (NtStatusHelper::isError(result)) return result;

    _hashObject.resize(hashObjectSize);
    _hash.resize(hashSize);

    return BCryptCreateHash(_algorithmHandle, &_hashHandle, _hashObject.data(), _hashObject.size(), nullptr, 0, 0);
}

NTSTATUS Hash::update(const std::vector<unsigned char> &content)
{
    auto pContent = const_cast<unsigned char*>(content.data());
    return BCryptHashData(_hashHandle, pContent, content.size(), 0);
}

NTSTATUS Hash::update(unsigned char* content, std::size_t size)
{
    return BCryptHashData(_hashHandle, content, size, 0);
}

NTSTATUS Hash::calculate()
{
    BCRYPT_HASH_HANDLE tmpHashHandle;

    auto result = BCryptDuplicateHash(_hashHandle, &tmpHashHandle, nullptr, 0, 0);
    if (NtStatusHelper::isError(result)) return result;

    result = BCryptFinishHash(tmpHashHandle, _hash.data(), _hash.size(), 0);
    if (NtStatusHelper::isError(result)) return result;

    BCryptDestroyHash(tmpHashHandle);

    return result;
}

NTSTATUS Hash::calculate(std::vector<unsigned char>& hash)
{
    auto result = calculate();
    if (NtStatusHelper::isError(result)) return result;

    hash = _hash;

    return result;
}

}
