#include "tree.h"
//#include "divider.cpp"

tree::tree()
{
    head = NULL;
}

void tree::deleting(item *h)
{
    if ( h->left)
    deleting(h->left);
    if (h->right)
    deleting(h->right);
    delete h;
}

tree::~tree()
{
    deleting( head);
}
/////////////////////////////////////////////////

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


die* divider(Cryptonite *A, int n)
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

    die *result = new die;

    result->left = new Cryptonite[cl];
    result->right = new Cryptonite[cr];

    for ( unsigned int i = 0; i < cl; ++i) result->left[i] = Left[i];
    for ( unsigned int i = 0; i < cr; ++i) result->right[i] =Right[i];

    result->l = cl;
    result->r = cr;


    return result;


}

//////////////////////////////////////////////////////////


void pushInTree(item*& head, Cryptonite* arr, int n, QString LorR, itemC*& output, int& k)
{
    if ( !head )
    {
        head = new item;

        head->left = head->right = NULL;

        head->elems = new Cryptonite[n + 1];

        for ( int i = 0; i < n; ++i)
        {
            head->elems[i].cha = arr[i].cha;

            head->elems[i].count = arr[i].count;
        }


        head->code.insert(head->code.length(), LorR);


///divide//started///

        if ( n > 1)
        {
/*
            Cryptonite *left = new Cryptonite[n-1], *right = new Cryptonite[n-1];
            int l = 0, r = 0;
            int CountL = 0, CountR = 0;

            for ( int i = 0; i < n; ++i)
            {
                if( CountL <= CountR)
                {
                    left[l].cha = arr[i].cha;

                    left[l].count = arr[i].count;

                    CountL += left[l++].count;
                }else{
                    right[r].cha = arr[i].cha;

                    right[r].count = arr[i].count;

                    CountR += right[r++].count;
                }

            }
            */

        Cryptonite *left = new Cryptonite[n-1], *right = new Cryptonite [n-1];
        int l, r;

        die *lucky;

        lucky = divider(arr, n);

        left = lucky->left;
        right = lucky->right;

        l = lucky->l;
        r = lucky->r;


///here i divided arr into left and right;

            QString codd = head->code;
            codd.insert(codd.length(), "0");
            pushInTree(head->left, left, l, codd, output, k);

            codd = head->code;
            codd.insert(codd.length(), "1");
            pushInTree(head->right, right, r, codd, output, k);

        }else{

            output[k].cha = head->elems->cha;



            output[k].count = head->code;

            ++k;
        }


    }else{
        return ;
    }
}

void tree::push(Cryptonite* arr, int n, QString LorR, itemC*& output, int& k)
{
   pushInTree(head, arr, n, LorR, output, k);

   q = k;

   result = new itemC[q];
   for ( int i = 0; i < q; ++i)
   {
       result[i].cha = output[i].cha;
       result[i].count = output[i].count;
   }
}
