#include <QtTest>

#include "hashtest.h"

int main()
{
    {
        Hashtest hashtest;
        QTest::qExec(&hashtest);
    }
    return 0;
}
