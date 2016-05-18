#ifndef CRYPTONITE_H
#define CRYPTONITE_H

#include <QMainWindow>

struct itemC
{
    QChar cha;

    QString count;
};

class Cryptonite
{
public:

    QChar cha;

    int count;

    Cryptonite();

    Cryptonite& operator = (const Cryptonite& first);
};

#endif // CRYPTONITE_H
