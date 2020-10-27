#ifndef TESTNTSTATUSHELPER_H
#define TESTNTSTATUSHELPER_H

#include <QObject>

class TestNtStatusHelper : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void givenErrorCode_shouldDetect_data();
    void givenErrorCode_shouldDetect();

    void givenSuccessCode_shouldDetect();

    void givenErrorCode_ShouldReturnItsStringDescription_data();
    void givenErrorCode_ShouldReturnItsStringDescription();
};

#endif // TESTNTSTATUSHELPER_H
