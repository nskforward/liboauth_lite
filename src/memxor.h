//
// Created by ishibkikh on 3/28/2018.
//

#ifndef LIBOAUTH_MEMXOR_H
#define LIBOAUTH_MEMXOR_H

#include <stddef.h>

/* Compute binary exclusive OR of memory areas DEST and SRC, putting
   the result in DEST, of length N bytes.  Returns a pointer to
   DEST. */
void *memxor (void */*restrict*/ dest, const void */*restrict*/ src, size_t n);

#endif //LIBOAUTH_MEMXOR_H
