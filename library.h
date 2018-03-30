//
// Created by ishibkikh on 3/30/2018.
//
#ifndef LIBOAUTH_LIBRARY_H
#define LIBOAUTH_LIBRARY_H

#include "src/oauth.h"

__declspec(dllexport) void oauth_sign_body(char *oauth_consumer_key, char *oauth_consumer_secret, char *http_method, char *http_url, char *http_post_body, char *out_body);

#endif //LIBOAUTH_LIBRARY_H
