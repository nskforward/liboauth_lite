//
// Created by ishibkikh on 3/29/2018.
//

#ifndef LIBOAUTH_BASE64_H
#define LIBOAUTH_BASE64_H

#include <stdlib.h>
#include <string.h>

int base64_decode(unsigned char *dest, const char *src);
char *base64_encode(int size, const unsigned char *src);

#endif //LIBOAUTH_BASE64_H
