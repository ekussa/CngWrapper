#ifndef TESTALGORITHMIDENTIFIERCOLLECTION_H
#define TESTALGORITHMIDENTIFIERCOLLECTION_H

#include <QObject>

class TestAlgorithmAlgorithmEnumerator : public QObject
{
    Q_OBJECT

public:
    TestAlgorithmAlgorithmEnumerator();

private Q_SLOTS:
    void shouldEnumerateSignature();
    void shouldEnumerateCipher();
    void shouldEnumerateHash();
    void shouldEnumerateAsymmetricEncryption();
    void shouldEnumerateSecretAgreement();
};


#endif // TESTALGORITHMIDENTIFIERCOLLECTION_H
