#include "testhash.h"

#include <QTest>
#include <numeric>

#include "hash.h"

using namespace CngWrapper;

void TestHash::shouldHaveSameHashLength_givenAlgorithmAndDynamicLengthInitializer_data()
{
    QTest::addColumn<QString>("algorithmName");
    QTest::addColumn<int>("expectedHashLength");

    QTest::newRow("SHA256")
            << QString::fromWCharArray(BCRYPT_SHA256_ALGORITHM)
            << 32;

    QTest::newRow("SHA384")
            << QString::fromWCharArray(BCRYPT_SHA384_ALGORITHM)
            << 48;

    QTest::newRow("SHA512")
            << QString::fromWCharArray(BCRYPT_SHA512_ALGORITHM)
            << 64;
}

void TestHash::shouldHaveSameHashLength_givenAlgorithmAndDynamicLengthInitializer()
{
    //Arrange
    QFETCH(QString, algorithmName);
    QFETCH(int, expectedHashLength);

    std::vector<unsigned char> content(30);
    std::iota(begin(content), end(content), 1);

    Hash hash(algorithmName.toStdWString());
    auto ret = hash.initialize();
    if(NtStatusHelper::isError(ret))
        QFAIL(NtStatusHelper::toString(ret).c_str());


    //Act
    ret = hash.update(content);
    if(NtStatusHelper::isError(ret))
        QFAIL(NtStatusHelper::toString(ret).c_str());

    ret = hash.calculate();
    if(NtStatusHelper::isError(ret))
        QFAIL(NtStatusHelper::toString(ret).c_str());

    auto& result = hash.get();


    //Assert
    QVERIFY(static_cast<int>(result.size()) == expectedHashLength);
}

void TestHash::shouldHaveSameHashLength_givenAlgorithmAndStaticLengthInitializer_data()
{
    QTest::addColumn<QString>("algorithmName");
    QTest::addColumn<int>("expectedHashLength");
    QTest::addColumn<int>("expectedHashObjectLength");

    QTest::newRow("SHA256")
            << QString::fromWCharArray(BCRYPT_SHA256_ALGORITHM)
            << 32 << 302;

    QTest::newRow("SHA384")
            << QString::fromWCharArray(BCRYPT_SHA384_ALGORITHM)
            << 48 << 382;

    QTest::newRow("SHA512")
            << QString::fromWCharArray(BCRYPT_SHA512_ALGORITHM)
            << 64 << 382;
}

void TestHash::shouldHaveSameHashLength_givenAlgorithmAndStaticLengthInitializer()
{
    //Arrange
    QFETCH(QString, algorithmName);
    QFETCH(int, expectedHashLength);
    QFETCH(int, expectedHashObjectLength);

    std::vector<unsigned char> content(30);
    std::iota(begin(content), end(content), 1);

    Hash hash(algorithmName.toStdWString());
    auto ret = hash.initialize(expectedHashLength, expectedHashObjectLength);
    if(NtStatusHelper::isError(ret))
        QFAIL(NtStatusHelper::toString(ret).c_str());


    //Act
    ret = hash.update(content);
    if(NtStatusHelper::isError(ret))
        QFAIL(NtStatusHelper::toString(ret).c_str());

    ret = hash.calculate();
    if(NtStatusHelper::isError(ret))
        QFAIL(NtStatusHelper::toString(ret).c_str());

    auto& result = hash.get();


    //Assert
    QVERIFY(static_cast<int>(result.size()) == expectedHashLength);
}

void TestHash::shouldReturnTheSameHash_whenTheSameDataisHashedInDifferentPortions()
{
    //Arrange
    const int hashObjectLength = 302, hashLength = 32, dataLength = 100;
    auto algorithmName = QString::fromWCharArray(BCRYPT_SHA256_ALGORITHM);
    std::vector<unsigned char> content(dataLength);
    std::iota(begin(content), end(content), 1);

    //Act
    std::vector<unsigned char> expectedHashResult;
    std::vector<unsigned char> multiUpdateHashResult;

    {
        Hash hash(algorithmName.toStdWString());
        auto ret = hash.initialize(hashLength, hashObjectLength);
        if(NtStatusHelper::isError(ret))
            QFAIL(NtStatusHelper::toString(ret).c_str());

        ret = hash.update(content);
        if(NtStatusHelper::isError(ret))
            QFAIL(NtStatusHelper::toString(ret).c_str());

        ret = hash.calculate();
        if(NtStatusHelper::isError(ret))
            QFAIL(NtStatusHelper::toString(ret).c_str());

        expectedHashResult = hash.get();
    }

    {
        auto part(dataLength/2);
        Hash hash(algorithmName.toStdWString());
        auto ret = hash.initialize(hashLength, hashObjectLength);
        if(NtStatusHelper::isError(ret))
            QFAIL(NtStatusHelper::toString(ret).c_str());

        ret = hash.update(content.data(), part);
        if(NtStatusHelper::isError(ret))
            QFAIL(NtStatusHelper::toString(ret).c_str());

        ret = hash.update(content.data() + part, part);
        if(NtStatusHelper::isError(ret))
            QFAIL(NtStatusHelper::toString(ret).c_str());

        ret = hash.calculate();
        if(NtStatusHelper::isError(ret))
            QFAIL(NtStatusHelper::toString(ret).c_str());

        multiUpdateHashResult = hash.get();
    }

    //Assert
    QVERIFY(std::equal(begin(multiUpdateHashResult), end(multiUpdateHashResult), begin(expectedHashResult)));
}

void TestHash::shouldReturnTheSameHash_whenHashReseted()
{
    //Arrange
    const int hashObjectLength = 302, hashLength = 32, dataLength = 100;
    auto algorithmName = QString::fromWCharArray(BCRYPT_SHA256_ALGORITHM);
    std::vector<unsigned char> content(dataLength);
    std::iota(begin(content), end(content), 1);

    //Act
    std::vector<unsigned char> expectedHashResult;
    std::vector<unsigned char> multiUpdateHashResult;

    {
        Hash hash(algorithmName.toStdWString());
        auto ret = hash.initialize(hashLength, hashObjectLength);
        if(NtStatusHelper::isError(ret))
            QFAIL(NtStatusHelper::toString(ret).c_str());

        ret = hash.update(content);
        if(NtStatusHelper::isError(ret))
            QFAIL(NtStatusHelper::toString(ret).c_str());

        ret = hash.calculate();
        if(NtStatusHelper::isError(ret))
            QFAIL(NtStatusHelper::toString(ret).c_str());

        expectedHashResult = hash.get();
    }

    auto part(dataLength/2);
    {
        Hash hash(algorithmName.toStdWString());
        auto ret = hash.initialize(hashLength, hashObjectLength);
        if(NtStatusHelper::isError(ret))
            QFAIL(NtStatusHelper::toString(ret).c_str());

        ret = hash.update(content.data(), part);
        if(NtStatusHelper::isError(ret))
            QFAIL(NtStatusHelper::toString(ret).c_str());

        ret = hash.calculate();
        if(NtStatusHelper::isError(ret))
            QFAIL(NtStatusHelper::toString(ret).c_str());

        ret = hash.update(content.data() + part, part);
        if(NtStatusHelper::isError(ret))
            QFAIL(NtStatusHelper::toString(ret).c_str());

        ret = hash.calculate();
        if(NtStatusHelper::isError(ret))
            QFAIL(NtStatusHelper::toString(ret).c_str());

        multiUpdateHashResult = hash.get();
    }

    //Assert
    QVERIFY(std::equal(begin(multiUpdateHashResult), end(multiUpdateHashResult), begin(expectedHashResult)));
}
