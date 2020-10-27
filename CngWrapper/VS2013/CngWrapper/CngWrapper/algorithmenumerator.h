#ifndef ALGORITHMIDENTIFIERCOLLECTION_H
#define ALGORITHMIDENTIFIERCOLLECTION_H

#include <windows.h>
#include <bcrypt.h>
#include <vector>
#include <string>

namespace CngWrapper
{

class AlgorithmEnumerator
{
    std::vector<std::wstring> _hashAlgorithms;
    std::vector<std::wstring> _cipher;
    std::vector<std::wstring> _hash;
    std::vector<std::wstring> _asymmetricEncryption;
    std::vector<std::wstring> _secretAgreement;

private:
    static NTSTATUS core(const unsigned long mode, std::vector<std::wstring>& output);

public:
    AlgorithmEnumerator();

    const std::vector<std::wstring>& getSignature();
    const std::vector<std::wstring>& getCipher();
    const std::vector<std::wstring>& getHash();
    const std::vector<std::wstring>& getAsymmetricEncryption();
    const std::vector<std::wstring>& getSecretArgeement();
};

}

#endif // ALGORITHMIDENTIFIERCOLLECTION_H
