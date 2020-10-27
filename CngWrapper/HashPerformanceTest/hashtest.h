#ifndef HASHTEST_H
#define HASHTEST_H

#include <QObject>

class Hashtest : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void shouldRunSuccessfully_data();
    void shouldRunSuccessfully();
};

#endif // HASHTEST_H
