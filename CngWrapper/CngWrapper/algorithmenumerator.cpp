#include "algorithmenumerator.h"

#include <algorithm>
#include "ntstatushelper.h"


namespace CngWrapper
{

NTSTATUS AlgorithmEnumerator::core(const unsigned long mode, std::vector<std::wstring>& output)
{
    BCRYPT_ALGORITHM_IDENTIFIER* hashAlgorithms;

    DWORD qty = 0;
    auto result = BCryptEnumAlgorithms(mode, &qty, &hashAlgorithms, 0);
    if(NtStatusHelper::isError(result))
        return result;

    for(DWORD i=0; i<qty; i++)
        output.push_back(hashAlgorithms[i].pszName);

    BCryptFreeBuffer(hashAlgorithms);

    return result;
}

AlgorithmEnumerator::AlgorithmEnumerator()
    :   _hashAlgorithms()
{
}

const std::vector<std::wstring> &AlgorithmEnumerator::getSignature()
{
    core(BCRYPT_SIGNATURE_OPERATION, _hashAlgorithms);
    return _hashAlgorithms;
}

const std::vector<std::wstring> &AlgorithmEnumerator::getCipher()
{
    core(BCRYPT_CIPHER_OPERATION, _cipher);
    return _cipher;
}

const std::vector<std::wstring> &AlgorithmEnumerator::getHash()
{
    core(BCRYPT_HASH_OPERATION, _hash);
    return _hash;
}

const std::vector<std::wstring> &AlgorithmEnumerator::getAsymmetricEncryption()
{
    core(BCRYPT_ASYMMETRIC_ENCRYPTION_OPERATION, _asymmetricEncryption);
    return _asymmetricEncryption;
}

const std::vector<std::wstring> &AlgorithmEnumerator::getSecretArgeement()
{
    core(BCRYPT_SECRET_AGREEMENT_OPERATION, _secretAgreement);
    return _secretAgreement;
}

}
