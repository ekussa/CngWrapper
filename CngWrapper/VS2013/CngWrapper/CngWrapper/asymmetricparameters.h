#ifndef ASYMMETRICPARAMETERS_H
#define ASYMMETRICPARAMETERS_H

#include <memory>
#include <string>

namespace CngWrapper
{

class AsymmetricParameters
{
public:
    const std::wstring _hashAlgorithmName, _publicKeynameAccessor, _privateKeynameAccessor;
	const std::wstring _signAlgorithmName;
	const unsigned long _signAlgorithmBitsQty;
	const unsigned long _extraFlags;
    void* _extraStructure;

    AsymmetricParameters(const std::wstring& hashAlgorithmName,
                         const std::wstring& publicKeyNameAccessor,
                         const std::wstring& privateKeynameAccessor,
                         const std::wstring& signAlgorithmName,
                         unsigned long signAlgorithmBitsQty,
                         unsigned long extraFlags = 0,
                         void* extraStructure = nullptr) :
        _hashAlgorithmName(hashAlgorithmName),
        _publicKeynameAccessor(publicKeyNameAccessor),
        _privateKeynameAccessor(privateKeynameAccessor),
        _signAlgorithmName(signAlgorithmName),
        _signAlgorithmBitsQty(signAlgorithmBitsQty),
        _extraFlags(extraFlags),
        _extraStructure(extraStructure)
    {
    }

    std::wstring toWString() const
    {
        std::wstring ret;
        ret.append(_signAlgorithmName);
        ret.append(std::to_wstring(_signAlgorithmBitsQty));
        ret.append(_hashAlgorithmName);
        return ret;
    }

    std::string toString() const
    {
        auto ret(toWString());
        return std::string(begin(ret), end(ret));
    }
};

}

#endif // ASYMMETRICPARAMETERS_H
