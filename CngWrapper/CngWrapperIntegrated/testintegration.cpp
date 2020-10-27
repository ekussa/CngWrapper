#include "testintegration.h"

#include <QtTest>
#include <QtDebug>
#include "ntstatushelper.h"
#include "asymmetricsignature.h"
#include "asymmetricparameters_instances.h"

using namespace CngWrapper;

void TestIntegration::shouldRunIntegrated_data()
{
    QTest::addColumn<int>("opaqueParameters");
    QTest::addColumn<int>("payloadlength");

    const auto max = 30;
    std::vector<int> vPayload;
    vPayload.reserve(max);
    vPayload.push_back(0);
    for(int i=0; i<max-1; i++) {
        vPayload.push_back(1 << i);
    }

    for(auto payload : vPayload)
    {
        QTest::newRow("")
                << reinterpret_cast<int>(rsa_sha256)
                << payload;

        QTest::newRow("")
                << reinterpret_cast<int>(ecdsa256_sha256)
                << payload;
    }
}

void TestIntegration::shouldRunIntegrated()
{
    QFETCH(int, opaqueParameters);
    QFETCH(int, payloadlength);

    auto& param = *reinterpret_cast<AsymmetricParameters*>(opaqueParameters);

   std::vector<unsigned char> content, privateKey, publicKey;


    AsymmetricSignature asyncmmetric(param);
    auto result = asyncmmetric.generate(privateKey, publicKey);
    if (NtStatusHelper::isError(result))
        QFAIL(NtStatusHelper::toString(result).c_str());

    content.resize(payloadlength);
    std::iota(begin(content), end(content), 0);

    qint64 sign, verif;

    QElapsedTimer elapsedTimer;
    elapsedTimer.start();

    {
        std::vector<unsigned char> signature;

        //Act
        {
            AsymmetricSignature asymmetricSignature(param);
            result = asymmetricSignature.sign(privateKey, content, signature);
            if (NtStatusHelper::isError(result))
                QFAIL(NtStatusHelper::toString(result).c_str());
        }
        sign = elapsedTimer.nsecsElapsed() / 1000;

        {
            AsymmetricSignature asymmetricSignature2(param);
            result = asymmetricSignature2.verify(publicKey, content, signature);
        }
        verif = elapsedTimer.nsecsElapsed() / 1000;
    }

    //Assert
    QVERIFY2(NtStatusHelper::isSuccess(result), NtStatusHelper::toString(result).c_str());

    qDebug() << payloadlength << "\t" << param.toString().c_str() << "\t" << sign << "\t" << verif;
}
