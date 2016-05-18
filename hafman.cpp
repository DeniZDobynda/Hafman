#include "hafman.h"

hafman::hafman()
{
    head = NULL;

    elems = NULL;
}

itemH* findMin(itemH *t)
{
    itemH *temp, *min;

    temp = min = t;

    while ( temp )
    {
        if ( temp->count <= min->count)
            if (temp->count < min->count)
            {
                min = temp;
            }else if (temp->howMuch <= min->howMuch)
            {
                min = temp;
            }
        temp = temp->next;
    }

    return min;
}

void hafman::removeItem( itemH *t )
{
    if ( head == t)
    {
        head = head->next;

        return ;
    }

    itemH *temp = new itemH;

    temp->next = head;

    while ( temp->next->ch != t->ch)
    {
        temp = temp->next;
    }
    temp->next = temp->next->next;
}

void hafman::add(QChar ch)
{
    itemH *t = new itemH;
    t->next = head;

    if ( !head)
    {
        head = new itemH;

        head->next = NULL;

        head->ch = ch;

        head->count = 1;

        return ;
    }

    while ( t->next )
    {
        if ( t->next->ch == ch)
        {
            ++t->next->count;

            return ;
        }

        t = t->next;
    }

    t->next = new itemH;

    t = t->next;

    t->ch = ch;

    t->count = 1;

    t->next = NULL;

}

hafman::hafman(QString str)
{
    head = NULL;
    elems = NULL;

    QString qstr;

    qstr.append(str);
    for ( int i = 0; i < qstr.length(); ++i)
    {
        QChar c = qstr.data()[i];

        this->add(c);

    }
    //here i have list from elems

    int n = 0;
    itemH *t;
    t = head;

    while ( t )
    {
        t = t->next;
        ++n;
    }

    elems = new itemH*[n+1];
    t = head;
    int i =0;
    while ( i < n )
    {
        elems[i] = t;

        ++i;

        t = t->next;
    }
    elems[i] = NULL;

    this->count = i-1;

    ///here i have backup of elems///

    if ( n != 1)
    {

        while ( head->next)
        {
            itemH *nev;  //first min

            nev = findMin(head);

            removeItem( nev);

            itemH *tem;   //second min

            tem = findMin(head);

            removeItem( tem);

            itemH *nevElem = new itemH;

            nev->next = nevElem;

            tem->next = nevElem;


            if( nev->count > tem->count)
            {
                nevElem->ch = tem->ch;
            }else{
                nevElem->ch = nev->ch;
            }


            nevElem->howMuch = std::max(nev->howMuch, tem->howMuch);

            ++nevElem->howMuch;

            nevElem->count = tem->count + nev->count;

            nevElem->next = head;

            head = nevElem;
        }

    }

}

QString hafman::getCode(QChar ch)
{
    QString result = "";
    if ( count > 1)
    {
        itemH *temp;
        int i = 0;
        while (elems[i]->ch != ch && i <= count) ++i;

        if ( i > count) return result;

        temp = elems[i];

        while ( temp->next)
        {
            if ( temp->next->ch == temp->ch)
            {
                result.insert(0, "0");
            }else{
                result.insert(0, "1");
            }
            temp = temp->next;
        }

        return result;
    }else{
        result.append("1");

        return result;
    }
}
//31354 vasya
struct dec
{
    QChar ch;

    QString code;
};

QString hafman::decode(QString textToDecode)
{
    QString result = "";

    int n = count+1;

    //while (elems[n] != NULL)++n;

    dec mass[n];

    for ( int i = 0; i <n; ++i)
    {
        mass[i].ch = elems[i]->ch;

        mass[i].code = this->getCode(elems[i]->ch);
    }
    ///have codes in "dec"
    ///

    for ( int i = 0; i < textToDecode.length(); )
    {
        dec copy[n];

        for ( int j = 0; j < n; ++j)
        {
            copy[j].ch = mass[j].ch;
            copy[j].code = mass[j].code;
        }
        //copiren

        int t = n;                  //for note, how much letters do i have

        int l = 0;

        if ( t != 1)
        {
            while ( t > 1 )
            {

                for ( int j = t-1; j >= 0; --j)
                {
                    if (copy[j].code.data()[l] != textToDecode.data()[i])
                    {
                        if ( j != t-1)
                        {
                            copy[j].ch = copy[t-1].ch;
                            copy[j].code = copy[t-1].code;

                        }
                        t--;
                    }
                }
                ++l;
                ++i;

                if ( i > textToDecode.length()) return "N";
            }

            if ( !t ) return "N";

            if ( t == 1 )
                result.append(copy[0].ch);


        }
    else{
        if ( textToDecode.data()[i++] != '1' ) return "N";

        result.append(copy[0].ch);
    }
    }
    return result;
}

QString hafman::getCodes()
{
    QString result = "";
    for ( unsigned short int i = 0; i <= count; ++i)
    {
        result.append(elems[i]->ch);
        result.append(" - ");
        result.append(this->getCode(elems[i]->ch));
        result.append("\n");
    }
    return result;
}
