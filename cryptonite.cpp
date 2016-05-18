#include "cryptonite.h"

Cryptonite::Cryptonite()
{
    count = 0;

}

Cryptonite& Cryptonite::operator = (const Cryptonite& first)
{
    this->cha = first.cha;

    this->count = first.count;

    return *this;
}
