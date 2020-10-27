#ifndef TESTHASH_H
#define TESTHASH_H

#include <QObject>

class TestHash : public QObject
{
    Q_OBJECT

private Q_SLOTS:
    void shouldHaveSameHashLength_givenAlgorithmAndDynamicLengthInitializer_data();
    void shouldHaveSameHashLength_givenAlgorithmAndDynamicLengthInitializer();

    void shouldHaveSameHashLength_givenAlgorithmAndStaticLengthInitializer_data();
    void shouldHaveSameHashLength_givenAlgorithmAndStaticLengthInitializer();

    void shouldReturnTheSameHash_whenTheSameDataisHashedInDifferentPortions();

    void shouldReturnTheSameHash_whenHashReseted();
};

#endif // TESTHASH_H
