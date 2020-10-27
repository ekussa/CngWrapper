#ifndef ASYMMETRICSIGNATURE_H
#define ASYMMETRICSIGNATURE_H

#include <vector>

#include "ntstatushelper.h"
#include "asymmetricparameters.h"

namespace CngWrapper
{

class AsymmetricSignature
{
    AsymmetricParameters& _param;

public:
    AsymmetricSignature(AsymmetricParameters& asymmetricParameters);
    ~AsymmetricSignature();

    NTSTATUS generate(std::vector<unsigned char>& privateKey, std::vector<unsigned char>& publicKey);

    NTSTATUS sign(const std::vector<unsigned char>& privateKey, const std::vector<unsigned char>& content, std::vector<unsigned char>& signature);

    NTSTATUS verify(const std::vector<unsigned char>& publicKey, const std::vector<unsigned char>& content, const std::vector<unsigned char>& signature);
};

}

#endif // ASYMMETRICSIGNATURE_H
