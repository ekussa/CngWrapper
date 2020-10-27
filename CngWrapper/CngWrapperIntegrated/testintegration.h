#ifndef TESTINTEGRATION_H
#define TESTINTEGRATION_H

#include <QObject>

class TestIntegration : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void shouldRunIntegrated_data();
    void shouldRunIntegrated();
};

#endif // TESTINTEGRATION_H
