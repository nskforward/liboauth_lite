//
// Created by ishibkikh on 3/28/2018.
//

#include "memxor.h"

void *memxor (void */*restrict*/ dest, const void */*restrict*/ src, size_t n)
{
    char const *s = (char const*)src;
    char *d = (char*)dest;
    for (; n > 0; n--)
        *d++ ^= *s++;
    return dest;
}