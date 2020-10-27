#include <QtTest>

#include "testintegration.h"

int main()
{
    {
        TestIntegration testIntegration;
        QTest::qExec(&testIntegration);
    }

    return 0;
}
