//
// Created by ishibkikh on 3/28/2018.
//

#ifndef LIBOAUTH_CRYPT_H
#define LIBOAUTH_CRYPT_H

#include "xmalloc.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdarg.h>
#include <time.h>
#include <math.h>
#include "sha1.h"

#ifndef ISXDIGIT
# define ISXDIGIT(x) (isxdigit((int) ((unsigned char)x)))
#endif

char *oauth_encode_base64(int size, const unsigned char *src);
int oauth_decode_base64(unsigned char *dest, const char *src);
char *oauth_url_escape(const char *string);
char *oauth_url_unescape(const char *string, size_t *olen);
char *oauth_catenc(int len, ...);
int oauth_split_post_paramters(const char *url, char ***argv, short qesc);
int oauth_split_url_parameters(const char *url, char ***argv);
char *oauth_serialize_url_sep (int argc, int start, char **argv, char *sep, int mod);
char *oauth_serialize_url (int argc, int start, char **argv);
char *oauth_gen_nonce();
char *oauth_sign_url2 (const char *url,
                       char **postargs,
                       const char *http_method, //< HTTP request method
                       const char *c_key, //< consumer key - posted plain text
                       const char *c_secret, //< consumer secret - used as 1st part of secret-key
                       const char *t_key, //< token key - posted plain text in URL
                       const char *t_secret //< token secret - used as 2st part of secret-key
);
char *oauth_sign_array2 (int *argcp,
                         char***argvp,
                         char **postargs,
                         const char *http_method, //< HTTP request method
                         const char *c_key, //< consumer key - posted plain text
                         const char *c_secret, //< consumer secret - used as 1st part of secret-key
                         const char *t_key, //< token key - posted plain text in URL
                         const char *t_secret //< token secret - used as 2st part of secret-key
);


#endif //LIBOAUTH_CRYPT_H
