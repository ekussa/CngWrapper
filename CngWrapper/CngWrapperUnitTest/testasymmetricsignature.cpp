#include <QtTest>
#include "testasymmetricsignature.h"

#include "asymmetricsignature.h"
#include "asymmetricparameters_instances.h"


using namespace CngWrapper;

void TestAsymmetricSignature::shouldAssertKeyGenerationLength_givenSignAlgorithm_data()
{
    QTest::addColumn<int>("opaqueParameters");
    QTest::addColumn<int>("expectedPrivateKeySize");
    QTest::addColumn<int>("expectedPublicKeySize");

    QTest::newRow("ECDSA 256")
            << reinterpret_cast<int>(ecdsa256_sha256)
            << 104 << 72;

    QTest::newRow("ECDSA 384")
            << reinterpret_cast<int>(ecdsa384_sha384)
            << 152 << 104;

    QTest::newRow("ECDSA 521")
            << reinterpret_cast<int>(ecdsa521_sha512)
            << 206 << 140;
}

void TestAsymmetricSignature::shouldAssertKeyGenerationLength_givenSignAlgorithm()
{
    //Arrange
    QFETCH(int, opaqueParameters);
    QFETCH(int, expectedPrivateKeySize);
    QFETCH(int, expectedPublicKeySize);

    auto& params = *reinterpret_cast<AsymmetricParameters*>(opaqueParameters);

    //Act
    std::vector<unsigned char> privateKey, publicKey;
    AsymmetricSignature sign(params);
    auto result = sign.generate(privateKey, publicKey);

    //Assert
    QVERIFY2(NtStatusHelper::isSuccess(result), NtStatusHelper::toString(result).c_str());
    QVERIFY(static_cast<int>(privateKey.size()) == expectedPrivateKeySize);
    QVERIFY(static_cast<int>(publicKey.size()) == expectedPublicKeySize);
}

void TestAsymmetricSignature::shouldMatchSignDatalength_givenSignAndHashAlgorithms_data()
{
    QTest::addColumn<int>("opaqueParameters");
    QTest::addColumn<int>("payloadlength");
    QTest::addColumn<int>("expectedSignatureLength");

    QTest::newRow("ECDSA 256 and SHA 256")
            << reinterpret_cast<int>(ecdsa256_sha256)
            << 1024 << 64;

    QTest::newRow("ECDSA 384 and SHA 384")
            << reinterpret_cast<int>(ecdsa384_sha384)
            << 1024 << 96;

    QTest::newRow("ECDSA 521 and SHA 512")
            << reinterpret_cast<int>(ecdsa521_sha512)
            << 1024 << 132;
}

void TestAsymmetricSignature::shouldMatchSignDatalength_givenSignAndHashAlgorithms()
{
    //Arrange
    QFETCH(int, opaqueParameters);
    QFETCH(int, payloadlength);
    QFETCH(int, expectedSignatureLength);

    auto& params = *reinterpret_cast<AsymmetricParameters*>(opaqueParameters);

    std::vector<unsigned char> privateKey, publicKey;

    AsymmetricSignature asymmetricSignature(params);

    auto result = asymmetricSignature.generate(privateKey, publicKey);
    QVERIFY2(NtStatusHelper::isSuccess(result), NtStatusHelper::toString(result).c_str());

    std::vector<unsigned char> content;
    content.resize(payloadlength);
    std::iota(begin(content), end(content), 0);

    //Act
    std::vector<unsigned char> signature;
    result = asymmetricSignature.sign(privateKey, content, signature);

    //Assert
    QVERIFY2(NtStatusHelper::isSuccess(result), NtStatusHelper::toString(result).c_str());
    QVERIFY(static_cast<int>(signature.size()) == expectedSignatureLength);
}
