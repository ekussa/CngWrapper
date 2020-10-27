#include <QTest>

#include "testntstatushelper.h"

#include "ntstatushelper.h"

using namespace CngWrapper;

void TestNtStatusHelper::givenErrorCode_shouldDetect_data()
{
    QTest::addColumn<NTSTATUS>("ntStatus");

    QTest::newRow("Invalid handle")
            << (long)STATUS_INVALID_HANDLE;

    QTest::newRow("Access violation")
            << (long)STATUS_ACCESS_VIOLATION;

    QTest::newRow("Invalid parameter")
            << (long)STATUS_INVALID_PARAMETER;

    QTest::newRow("No memory")
            << (long)STATUS_NO_MEMORY;
}

void TestNtStatusHelper::givenErrorCode_shouldDetect()
{
    //Arrange
    QFETCH(NTSTATUS, ntStatus);

    //Assert
    QVERIFY(NtStatusHelper::isError(ntStatus) == true);
    QVERIFY(NtStatusHelper::isSuccess(ntStatus) == false);
}

void TestNtStatusHelper::givenSuccessCode_shouldDetect()
{
    //Assert
    QVERIFY(NtStatusHelper::isError(0) == false);
    QVERIFY(NtStatusHelper::isSuccess(0) == true);
}

void TestNtStatusHelper::givenErrorCode_ShouldReturnItsStringDescription_data()
{
    QTest::addColumn<NTSTATUS>("ntStatus");
    QTest::addColumn<QString>("description");

    QTest::newRow("Invalid handle")
            << (long)STATUS_INVALID_HANDLE
            << QString("An invalid HANDLE was specified.\r\n");

    QTest::newRow("Access violation")
            << (long)STATUS_ACCESS_VIOLATION
            << QString("The instruction at 0x");

    QTest::newRow("Invalid parameter")
            << (long)STATUS_INVALID_PARAMETER
            << QString("An invalid parameter was passed to a service or function.\r\n");

    QTest::newRow("No memory")
            << (long)STATUS_NO_MEMORY
            << QString("{Not Enough Quota}\r\nNot enough virtual memory or paging file quota is available to complete the specified operation.\r\n");
}

void TestNtStatusHelper::givenErrorCode_ShouldReturnItsStringDescription()
{
    //Arrange
    QFETCH(NTSTATUS, ntStatus);
    QFETCH(QString, description);

    //Act
    std::string result = NtStatusHelper::toString(ntStatus);
    std::wstring wResult = NtStatusHelper::toWString(ntStatus);

    //Assert
    QVERIFY(result == description.toStdString());
    QVERIFY(wResult == description.toStdWString());
}
