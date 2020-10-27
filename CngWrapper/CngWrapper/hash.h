#ifndef HASH_H
#define HASH_H

#include <vector>

#include "ntstatushelper.h"

namespace CngWrapper
{

class Hash
{
    BCRYPT_ALG_HANDLE _algorithmHandle;
    BCRYPT_HASH_HANDLE _hashHandle;
    std::wstring _algorithmName;

    std::vector<unsigned char> _hash, _hashObject;

public:
    Hash(const std::wstring& algorithmName);
    ~Hash();

    NTSTATUS initialize();

    NTSTATUS initialize(const std::size_t hashSize, const std::size_t hashObjectSize);

    NTSTATUS update(const std::vector<unsigned char> &content);

    NTSTATUS update(unsigned char* content, std::size_t size);

    NTSTATUS calculate();

    NTSTATUS calculate(std::vector<unsigned char>& hash);

    const std::vector<unsigned char>& get() const { return _hash; }
};

}

#endif // HASH_H
