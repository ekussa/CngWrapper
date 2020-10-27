#include <QtTest>

#include "testalgorithmidentifiercollection.h"
#include "algorithmenumerator.h"

using namespace CngWrapper;

TestAlgorithmAlgorithmEnumerator::TestAlgorithmAlgorithmEnumerator()
{
}

void TestAlgorithmAlgorithmEnumerator::shouldEnumerateSignature()
{
    //Arrange
    AlgorithmEnumerator algorithmEnumerator;

    //Act
    auto result(algorithmEnumerator.getAsymmetricEncryption());

    //Assert
    QVERIFY(!result.empty());
}

void TestAlgorithmAlgorithmEnumerator::shouldEnumerateCipher()
{
    //Arrange
    AlgorithmEnumerator algorithmEnumerator;

    //Act
    auto result(algorithmEnumerator.getCipher());

    //Assert
    QVERIFY(!result.empty());
}

void TestAlgorithmAlgorithmEnumerator::shouldEnumerateHash()
{
    //Arrange
    AlgorithmEnumerator algorithmEnumerator;

    //Act
    auto result(algorithmEnumerator.getHash());

    //Assert
    QVERIFY(!result.empty());
}

void TestAlgorithmAlgorithmEnumerator::shouldEnumerateAsymmetricEncryption()
{
    //Arrange
    AlgorithmEnumerator algorithmEnumerator;

    //Act
    auto result(algorithmEnumerator.getAsymmetricEncryption());

    //Assert
    QVERIFY(!result.empty());
}

void TestAlgorithmAlgorithmEnumerator::shouldEnumerateSecretAgreement()
{
    //Arrange
    AlgorithmEnumerator algorithmEnumerator;

    //Act
    auto result(algorithmEnumerator.getSecretArgeement());

    //Assert
    QVERIFY(!result.empty());
}
