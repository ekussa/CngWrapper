#include "hashtest.h"

#include <QtTest>
#include <QtDebug>
#include "hash.h"
#include "algorithmenumerator.h"

using namespace CngWrapper;

void Hashtest::shouldRunSuccessfully_data()
{
    QTest::addColumn<QString>("hashAlgorithmName");
    QTest::addColumn<int>("payloadlength");

    const auto max = 30;
    std::vector<int> vPayload;
    vPayload.reserve(max);
    vPayload.push_back(0);
    for(int i=0; i<max-1; i++) {
        vPayload.push_back(1 << i);
    }

    AlgorithmEnumerator algorithmEnumerator;
    auto vHash(algorithmEnumerator.getHash());

    for(auto payload : vPayload)
    {
        for(auto hash : vHash)
        {
            QTest::newRow("")
                    << QString::fromWCharArray(hash.c_str())
                    << payload;
        }
    }
}

void Hashtest::shouldRunSuccessfully()
{
    QFETCH(QString, hashAlgorithmName);
    QFETCH(int, payloadlength);

    std::vector<unsigned char> content;
    content.resize(payloadlength);
    std::iota(begin(content), end(content), 0);

    qint64 sign;

    QElapsedTimer elapsedTimer;
    elapsedTimer.start();
    //for(unsigned long i=0; i<2; i++)
    {
        //Act
        Hash hash(hashAlgorithmName.toStdWString());
        auto result = hash.initialize();
        if(NtStatusHelper::isError(result))
            QFAIL(NtStatusHelper::toString(result).c_str());

        result = hash.update(content);
        if(NtStatusHelper::isError(result))
            QFAIL(NtStatusHelper::toString(result).c_str());

        result = hash.calculate();
        if(NtStatusHelper::isError(result))
            QFAIL(NtStatusHelper::toString(result).c_str());

        sign = elapsedTimer.nsecsElapsed() / 1000;

        //Assert
        QVERIFY2(NtStatusHelper::isSuccess(result), NtStatusHelper::toString(result).c_str());
    }

    qDebug() << payloadlength << " \t" << hashAlgorithmName << "\t sign: \t" << sign;
}
