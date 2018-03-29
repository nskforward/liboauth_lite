//
// Created by ishibkikh on 3/29/2018.
//

#include "base64.h"
#include "xmalloc.h"

char char_b64encode(unsigned char u)
{
    if(u < 26)  return (char)('A'+u);
    if(u < 52)  return (char)('a'+(u-26));
    if(u < 62)  return (char)('0'+(u-52));
    if(u == 62) return '+';
    return '/';
}


unsigned char char_b64decode(char c)
{
    if(c >= 'A' && c <= 'Z') return(c - 'A');
    if(c >= 'a' && c <= 'z') return(c - 'a' + 26);
    if(c >= '0' && c <= '9') return(c - '0' + 52);
    if(c == '+')             return 62;
    return 63;
}


int char_is_base64(char c)
{
    if((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') ||
       (c >= '0' && c <= '9') || (c == '+')             ||
       (c == '/')             || (c == '=')) {
        return 1;
    }
    return 0;
}


char *base64_encode(int size, const unsigned char *src)
{
    int i;
    char *out, *p;

    if(!src) return NULL;
    if(!size) size= strlen((char *)src);
    out= (char*) xcalloc(sizeof(char), (size_t)size*4/3+4);
    p= out;

    for(i=0; i<size; i+=3) {
        unsigned char b1=0, b2=0, b3=0, b4=0, b5=0, b6=0, b7=0;
        b1= src[i];
        if(i+1<size) b2= src[i+1];
        if(i+2<size) b3= src[i+2];

        b4= b1>>2;
        b5= ((b1&0x3)<<4)|(b2>>4);
        b6= ((b2&0xf)<<2)|(b3>>6);
        b7= b3&0x3f;

        *p++= char_b64encode(b4);
        *p++= char_b64encode(b5);

        if(i+1<size) *p++= char_b64encode(b6);
        else *p++= '=';

        if(i+2<size) *p++= char_b64encode(b7);
        else *p++= '=';
    }
    return out;
}


int base64_decode(unsigned char *dest, const char *src)
{
    if(src && *src) {
        unsigned char *p= dest;
        int k, l= strlen(src)+1;
        unsigned char *buf= (unsigned char*) xcalloc(sizeof(unsigned char), l);

        /* Ignore non base64 chars as per the POSIX standard */
        for(k=0, l=0; src[k]; k++) {
            if(char_is_base64(src[k])) {
                buf[l++]= src[k];
            }
        }

        for(k=0; k<l; k+=4) {
            char c1='A', c2='A', c3='A', c4='A';
            unsigned char b1=0, b2=0, b3=0, b4=0;
            c1= buf[k];

            if(k+1<l) c2= buf[k+1];
            if(k+2<l) c3= buf[k+2];
            if(k+3<l) c4= buf[k+3];

            b1= char_b64decode(c1);
            b2= char_b64decode(c2);
            b3= char_b64decode(c3);
            b4= char_b64decode(c4);

            *p++=((b1<<2)|(b2>>4) );

            if(c3 != '=') *p++=(((b2&0xf)<<4)|(b3>>2) );
            if(c4 != '=') *p++=(((b3&0x3)<<6)|b4 );
        }
        xfree(buf);
        dest[p-dest]='\0';
        return(p-dest);
    }
    return 0;
}