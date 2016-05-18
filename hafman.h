#ifndef HAFMAN_H
#define HAFMAN_H

#include <QMainWindow>

struct itemH
{
    QChar ch;

    int count;

    int howMuch = 0;

    itemH *next;
};

class hafman
{
public:

    itemH *head;

    hafman();

    hafman(QString);

    itemH **elems;

    int count;

    QString getCode(QChar);             /// real coding///

    QString getChar (QString);              //decode word

    void add(QChar );

    void removeItem(itemH *t);

    QString getCodes();

    QString decode(QString);                ///real decoding///
};

#endif // HAFMAN_H
