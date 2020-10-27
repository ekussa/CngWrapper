#ifndef ASYMMETRICSIGNATURE_H
#define ASYMMETRICSIGNATURE_H

#include <vector>

#include "ntstatushelper.h"
#include "asymmetricparameters.h"

namespace CngWrapper
{

class AsymmetricSignature
{
	BCRYPT_ALG_HANDLE _algorithmHandle;
	BCRYPT_KEY_HANDLE _keyHandle;
	
	AsymmetricParameters& _param;

public:
    AsymmetricSignature(AsymmetricParameters& asymmetricParameters);
    ~AsymmetricSignature();

    NTSTATUS generate(std::vector<unsigned char>& privateKey, std::vector<unsigned char>& publicKey);

	NTSTATUS importPrivateKey(const std::vector<unsigned char>& privateKey);

	NTSTATUS importPublicKey(const std::vector<unsigned char>& publicKey);

	NTSTATUS signHash(const std::vector<unsigned char>& hashData, std::vector<unsigned char>& signature) const;
	
	NTSTATUS verifyHash(const std::vector<unsigned char>& hashData, const std::vector<unsigned char>& signature) const;

	NTSTATUS sign(const std::vector<unsigned char>& privateKey, const std::vector<unsigned char>& content, std::vector<unsigned char>& signature) const;

    NTSTATUS verify(const std::vector<unsigned char>& publicKey, const std::vector<unsigned char>& content, const std::vector<unsigned char>& signature) const;
};

}

#endif // ASYMMETRICSIGNATURE_H
