#include <QtTest>

#include "testalgorithmidentifiercollection.h"
#include "testasymmetricsignature.h"
#include "testntstatushelper.h"
#include "testhash.h"

int main()
{
    {
        TestHash testHash;
        QTest::qExec(&testHash);
    }

    {
        TestAlgorithmAlgorithmEnumerator testalgorithmidentifiercollection;
        QTest::qExec(&testalgorithmidentifiercollection);
    }

    {
        TestAsymmetricSignature testAsymmetricSignature;
        QTest::qExec(&testAsymmetricSignature);
    }

    {
        TestNtStatusHelper testNtStatusHelper;
        QTest::qExec(&testNtStatusHelper);
    }

    return 0;
}
