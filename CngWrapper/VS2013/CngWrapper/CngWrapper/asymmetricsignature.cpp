#include "asymmetricsignature.h"

#include "hash.h"

namespace CngWrapper
{

AsymmetricSignature::AsymmetricSignature(AsymmetricParameters &asymmetricParameters) :
	_algorithmHandle(nullptr),
	_keyHandle(nullptr),
	_param(asymmetricParameters)
{
}

AsymmetricSignature::~AsymmetricSignature()
{
	if (_algorithmHandle)
		BCryptCloseAlgorithmProvider(_algorithmHandle, 0);

	if (_keyHandle)
		BCryptDestroyKey(_keyHandle);
}

NTSTATUS AsymmetricSignature::generate(std::vector<unsigned char> &privateKey, std::vector<unsigned char> &publicKey)
{
    BCRYPT_ALG_HANDLE algorithmHandle;
    BCRYPT_KEY_HANDLE keyHandle;

    //Create handles
    auto result = BCryptOpenAlgorithmProvider(&algorithmHandle, _param._signAlgorithmName.c_str(), nullptr, 0);
    if (NtStatusHelper::isError(result)) return result;


    //Generating keys
    result = BCryptGenerateKeyPair(algorithmHandle, &keyHandle, _param._signAlgorithmBitsQty, 0);
    if (NtStatusHelper::isError(result)) return result;

    result = BCryptFinalizeKeyPair(keyHandle, 0);
    if (NtStatusHelper::isError(result)) return result;


    //Exporting keys
    unsigned long keySize;
    result = BCryptExportKey(keyHandle, nullptr, _param._privateKeynameAccessor.c_str(), nullptr, 0, &keySize, 0);
    if (NtStatusHelper::isError(result)) return result;

    privateKey.resize(keySize);
    unsigned long reserved = 0;
    result = BCryptExportKey(keyHandle, nullptr, _param._privateKeynameAccessor.c_str(), privateKey.data(), privateKey.size(), &reserved, 0);
    if (NtStatusHelper::isError(result)) return result;


    result = BCryptExportKey(keyHandle, nullptr, _param._publicKeynameAccessor.c_str(), nullptr, 0, &keySize, 0);
    if (NtStatusHelper::isError(result)) return result;

    publicKey.resize(keySize);
    result = BCryptExportKey(keyHandle, nullptr, _param._publicKeynameAccessor.c_str(), publicKey.data(), publicKey.size(), &reserved, 0);
    if (NtStatusHelper::isError(result)) return result;

    //Releasing handles
    BCryptDestroyKey(keyHandle);
    BCryptCloseAlgorithmProvider(algorithmHandle, 0);


    return result;
}

NTSTATUS AsymmetricSignature::importPrivateKey(const std::vector<unsigned char>& privateKey)
{
	//Create handle
	auto result = BCryptOpenAlgorithmProvider(&_algorithmHandle, _param._signAlgorithmName.c_str(), nullptr, 0);
	if (NtStatusHelper::isError(result)) return result;

	//Import key
	return BCryptImportKeyPair(_algorithmHandle, nullptr, _param._privateKeynameAccessor.c_str(), &_keyHandle, const_cast<unsigned char*>(privateKey.data()), privateKey.size(), 0);
}

NTSTATUS AsymmetricSignature::importPublicKey(const std::vector<unsigned char>& publicKey)
{
	//Create handle
	auto result = BCryptOpenAlgorithmProvider(&_algorithmHandle, _param._signAlgorithmName.c_str(), nullptr, 0);
	if (NtStatusHelper::isError(result)) return result;

	//Import key
	return BCryptImportKeyPair(_algorithmHandle, nullptr, _param._publicKeynameAccessor.c_str(), &_keyHandle, const_cast<unsigned char*>(publicKey.data()), publicKey.size(), 0);
}

NTSTATUS AsymmetricSignature::signHash(const std::vector<unsigned char>& hashData, std::vector<unsigned char>& signature) const
{
	unsigned long signatureSize = 0;
	auto pHashData(const_cast<unsigned char*>(hashData.data()));
	auto result = BCryptSignHash(_keyHandle, nullptr, pHashData, hashData.size(), nullptr, 0, &signatureSize, 0);
	if (NtStatusHelper::isError(result)) return result;
	signature.resize(signatureSize);

	unsigned long reserved = 0;
	return BCryptSignHash(_keyHandle, _param._extraStructure, pHashData, hashData.size(), signature.data(), signature.size(), &reserved, _param._extraFlags);
}

NTSTATUS AsymmetricSignature::verifyHash(const std::vector<unsigned char>& hashData, const std::vector<unsigned char>& signature) const
{
	return BCryptVerifySignature(_keyHandle, _param._extraStructure, const_cast<unsigned char*>(hashData.data()), hashData.size(), const_cast<unsigned char*>(signature.data()), signature.size(), _param._extraFlags);
}

NTSTATUS AsymmetricSignature::sign(const std::vector<unsigned char> &privateKey, const std::vector<unsigned char> &content, std::vector<unsigned char> &signature) const
{
    BCRYPT_ALG_HANDLE algorithmHandle;
    BCRYPT_KEY_HANDLE keyHandle;

    //Create handle
    auto result = BCryptOpenAlgorithmProvider(&algorithmHandle, _param._signAlgorithmName.c_str(), nullptr, 0);
    if (NtStatusHelper::isError(result)) return result;

    //Import key
    result = BCryptImportKeyPair(algorithmHandle, nullptr, _param._privateKeynameAccessor.c_str(), &keyHandle, const_cast<unsigned char*>(privateKey.data()), privateKey.size(), 0);
    if (NtStatusHelper::isError(result)) return result;


    //Hash data
    Hash hash(_param._hashAlgorithmName);
    result = hash.initialize();
    if (NtStatusHelper::isError(result)) return result;

    result = hash.update(content);
    if (NtStatusHelper::isError(result)) return result;

    result = hash.calculate();
    if (NtStatusHelper::isError(result)) return result;

    std::vector<unsigned char> hashData = hash.get();


    //Sign hash
    unsigned long signatureSize = 0;
    auto pHashData(const_cast<unsigned char*>(hashData.data()));
    result = BCryptSignHash(keyHandle, nullptr, pHashData, hashData.size(), nullptr, 0, &signatureSize, 0);
    if (NtStatusHelper::isError(result)) return result;
    signature.resize(signatureSize);

    unsigned long reserved = 0;
    result = BCryptSignHash(keyHandle, _param._extraStructure, pHashData, hashData.size(), signature.data(), signature.size(), &reserved, _param._extraFlags);
    if (NtStatusHelper::isError(result)) return result;

    //Release all
    BCryptDestroyKey(keyHandle);
    BCryptCloseAlgorithmProvider(algorithmHandle, 0);

    return result;
}

NTSTATUS AsymmetricSignature::verify(const std::vector<unsigned char>& publicKey, const std::vector<unsigned char> &content, const std::vector<unsigned char> &signature) const
{
    BCRYPT_ALG_HANDLE algorithmHandle;
    BCRYPT_KEY_HANDLE keyHandle;

    //Create handle
    auto result = BCryptOpenAlgorithmProvider(&algorithmHandle, _param._signAlgorithmName.c_str(), nullptr, 0);
    if (NtStatusHelper::isError(result)) return result;

    //Import key
    result = BCryptImportKeyPair(algorithmHandle, nullptr, _param._publicKeynameAccessor.c_str(), &keyHandle, const_cast<unsigned char*>(publicKey.data()), publicKey.size(), 0);
    if (NtStatusHelper::isError(result)) return result;


    //Hash data
    Hash hash(_param._hashAlgorithmName);
    result = hash.initialize();
    if (NtStatusHelper::isError(result)) return result;

    result = hash.update(content);
    if (NtStatusHelper::isError(result)) return result;

    result = hash.calculate();
    if (NtStatusHelper::isError(result)) return result;

    std::vector<unsigned char> hashData = hash.get();


    //Verify hash
    result = BCryptVerifySignature(keyHandle, _param._extraStructure, hashData.data(), hashData.size(), const_cast<unsigned char*>(signature.data()), signature.size(), _param._extraFlags);
    if (NtStatusHelper::isError(result)) return result;

    //Release all
    BCryptDestroyKey(keyHandle);
    BCryptCloseAlgorithmProvider(algorithmHandle, 0);

    return result;
}

}
