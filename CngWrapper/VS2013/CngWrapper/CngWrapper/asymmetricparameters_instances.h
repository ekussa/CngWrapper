#ifndef ASYMMETRICPARAMETERS_INSTANCED_H
#define ASYMMETRICPARAMETERS_INSTANCED_H

#include <bcrypt.h>
#include "asymmetricparameters.h"

namespace CngWrapper
{
AsymmetricParameters rsa_sha256(
        BCRYPT_SHA256_ALGORITHM,
        BCRYPT_RSAPUBLIC_BLOB,
        BCRYPT_RSAPRIVATE_BLOB,
        BCRYPT_RSA_ALGORITHM,
        2048,
        BCRYPT_PAD_PKCS1,
        reinterpret_cast<void*>(new BCRYPT_PKCS1_PADDING_INFO()));

AsymmetricParameters ecdsa256_sha256(
        BCRYPT_SHA256_ALGORITHM,
        BCRYPT_ECCPUBLIC_BLOB,
        BCRYPT_ECCPRIVATE_BLOB,
        BCRYPT_ECDSA_P256_ALGORITHM,
        256);

AsymmetricParameters ecdsa384_sha384(
        BCRYPT_SHA384_ALGORITHM,
        BCRYPT_ECCPUBLIC_BLOB,
        BCRYPT_ECCPRIVATE_BLOB,
        BCRYPT_ECDSA_P384_ALGORITHM,
        384);

AsymmetricParameters ecdsa521_sha512(
        BCRYPT_SHA512_ALGORITHM,
        BCRYPT_ECCPUBLIC_BLOB,
        BCRYPT_ECCPRIVATE_BLOB,
        BCRYPT_ECDSA_P521_ALGORITHM,
        521);
}

#endif // ASYMMETRICPARAMETERS_INSTANCED_H
