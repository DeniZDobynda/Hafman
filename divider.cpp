#include <QMainWindow>
#include "cryptonite.h"
#include <stdlib.h>

class die
{
public:
    Cryptonite *left, *right;
    int l, r;
};


int Partition ( Cryptonite*& A, int left, int right)
{
    int x = A[left].count;

    int i = left - 1;

    for ( int j = left; j < right - 1; ++j)
    {
        if ( A[j].count <= x)
        {
            ++i;
            std::swap(A[i], A[j]);
        }


    }
    ++i;
    std::swap(A[i], A[right]);
    return i;
}

void quickSort ( Cryptonite*& A, int left, int right)
{
    if ( left >= right) return ;

    int i = Partition(A, left, right);
    quickSort(A, left, i-1);
    quickSort(A, i+1, right);

}


die& divider(Cryptonite *A, int n)
{

    Cryptonite max;
    max = A[0];
    int j = 0;
    for ( int i = 1; i < n; ++i)
    {
        if ( max.count < A[i].count)
        {
            max = A[i];
            j = i;
        }
    }
    ///founded max///

    A[j] = A[n-1];

    --n;

    A[n].count = 0;

    Cryptonite Left[n-1], Right[n-1];

    int cl = 0, cr = 0, countL = 0, countR = 0;

    Right[cr] = max;

    cr++;

    countR = max.count;



    while ( n >= 2)
    {
        int S[n-1];

        quickSort(A, 0, n-1);

        for ( int i = 0; i < n-1; ++i)
        {

            S[i] = A[i+1].count - A[i].count;

            if ( i == 0)
            {
                max.count = S[i];
                j = i;
            }else{
                if ( max.count <= S[i])
                {
                    max.count = S[i];

                    j = i;
                }
            }
        }

        if ( countL <= countR)
        {
            Left[cl] = A[j+1];
            ++cl;
            countL += A[j+1].count;
        }else{
            Right[cr] = A[j+1];
            cr++;
            countR += A[j+1].count;
        }

        A[j+1] = A[n-1];

        n--;

    }
    if ( countL <= countR)
    {
        Left[cl] = A[0];
        ++cl;
        countL += A[0].count;
    }else{
        Right[cr] = A[0];
        cr++;
        countR += A[0].count;
    }

    die result;

    result.left = Left;
    result.right =Right;

    result.l = cl;
    result.r = cr;


    return result;


}
