#ifndef TESTASYMMETRICSIGNATURE_H
#define TESTASYMMETRICSIGNATURE_H

#include <QObject>

class TestAsymmetricSignature : public QObject
{
    Q_OBJECT

private Q_SLOTS:

    void shouldAssertKeyGenerationLength_givenSignAlgorithm_data();
    void shouldAssertKeyGenerationLength_givenSignAlgorithm();

    void shouldMatchSignDatalength_givenSignAndHashAlgorithms_data();
    void shouldMatchSignDatalength_givenSignAndHashAlgorithms();
};

#endif // TESTASYMMETRICSIGNATURE_H
