//
// Created by ishibkikh on 3/29/2018.
//

#ifndef LIBOAUTH_OAUTH_H
#define LIBOAUTH_OAUTH_H

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

#define MAX_OAUTH_PARAMS 64

typedef struct {
    char *key;
    char *value;
} OAuthParameter;

typedef struct {
    OAuthParameter **items;
    size_t count;
} OAuthParameterCollection;


OAuthParameter * oauth_param_init(char *key, char *value);
OAuthParameterCollection * oauth_collection_init();
void oauth_collection_destroy(OAuthParameterCollection *collection);
void oauth_param_destroy(OAuthParameter *param);
void oauth_collection_add_params(OAuthParameterCollection* collection, char *data);
void oauth_collection_add_url_params(OAuthParameterCollection* collection, const char *url);
void oauth_collection_print_params(OAuthParameterCollection *collection);
char *oauth_url_unescape(const char *string, size_t *olen);
char *oauth_url_escape(const char *string);
int oauth_collection_param_key_exists(OAuthParameterCollection* collection, char *key);
char * oauth_sign_post(char*url, char*post_data, char*consumer_key, char *consumer_secret);
void oauth_collection_add_specific_params(OAuthParameterCollection *collection, char *consumer_key);
char *oauth_gen_nonce(int len);
char *oauth_get_timestamp();
void oauth_collection_sort(OAuthParameterCollection *collection);
char *oauth_collection_join(OAuthParameterCollection* collection);


#endif //LIBOAUTH_OAUTH_H
