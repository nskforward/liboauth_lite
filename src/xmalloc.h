#ifndef _OAUTH_XMALLOC_H
#define _OAUTH_XMALLOC_H      1

#include <stdlib.h>

/* Prototypes for functions defined in xmalloc.c  */
void *xmalloc (size_t size);
void *xcalloc (size_t nmemb, size_t size);
void *xrealloc (void *ptr, size_t size);
char *xstrdup (const char *s);
void xfree(void *ptr);
void *memdup(void *src, size_t size);

#endif