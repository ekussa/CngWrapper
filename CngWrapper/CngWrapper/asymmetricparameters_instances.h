#ifndef ASYMMETRICPARAMETERS_INSTANCED_H
#define ASYMMETRICPARAMETERS_INSTANCED_H

#include "asymmetricparameters.h"

namespace CngWrapper
{
auto rsa_sha256 = new AsymmetricParameters (
        BCRYPT_SHA256_ALGORITHM,
        BCRYPT_RSAPUBLIC_BLOB,
        BCRYPT_RSAPRIVATE_BLOB,
        BCRYPT_RSA_ALGORITHM,
        2048,
        BCRYPT_PAD_PKCS1,
        reinterpret_cast<void*>(new BCRYPT_PKCS1_PADDING_INFO()));

auto ecdsa256_sha256 = new AsymmetricParameters (
        BCRYPT_SHA256_ALGORITHM,
        BCRYPT_ECCPUBLIC_BLOB,
        BCRYPT_ECCPRIVATE_BLOB,
        BCRYPT_ECDSA_P256_ALGORITHM,
        256);

auto ecdsa384_sha384 = new AsymmetricParameters (
        BCRYPT_SHA384_ALGORITHM,
        BCRYPT_ECCPUBLIC_BLOB,
        BCRYPT_ECCPRIVATE_BLOB,
        BCRYPT_ECDSA_P384_ALGORITHM,
        384);

auto ecdsa521_sha512 = new AsymmetricParameters (
        BCRYPT_SHA512_ALGORITHM,
        BCRYPT_ECCPUBLIC_BLOB,
        BCRYPT_ECCPRIVATE_BLOB,
        BCRYPT_ECDSA_P521_ALGORITHM,
        521);
}

#endif // ASYMMETRICPARAMETERS_INSTANCED_H
