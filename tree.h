#ifndef TREE_H
#define TREE_H

#include "QMainWindow"
#include "cryptonite.h"

struct item
{
    Cryptonite* elems;

    QString code;

    item *left, *right;
};



class tree
{
public:

    item *head;

    itemC *result;

    int q;

    tree();

    ~tree();

    void push ( Cryptonite *arr, int n, QString LorR , itemC*& output, int& k  );

    void deleting(item *h);

    QString getCode(QChar);

};


#endif // TREE_H
