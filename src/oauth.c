//
// Created by ishibkikh on 3/29/2018.
//

#include <time.h>
#include "oauth.h"
#include "sha1.h"
#include "base64.h"
#include "xmalloc.h"

OAuthParameterCollection * oauth_collection_init()
{
    OAuthParameterCollection *collection = malloc(sizeof(OAuthParameterCollection));
    collection->count = 0;
    collection->items = calloc(MAX_OAUTH_PARAMS, sizeof(OAuthParameter *));
}

void oauth_collection_destroy(OAuthParameterCollection *collection)
{
    for (int i=0; i < collection->count; i++){
        OAuthParameter *param = collection->items[i];
        oauth_param_destroy(param);
    }
    free(collection->items);
    free(collection);
}

void oauth_collection_print_params(OAuthParameterCollection *collection)
{
    printf("-------------------------------\n");
    printf("%i parameters\n", collection->count);
    printf("-------------------------------\n");
    for (int i=0; i<collection->count; i++){
        OAuthParameter *param = collection->items[i];
        printf("|%s=%s|\n", param->key, param->value);
    }
    printf("-------------------------------\n");
}

OAuthParameter * oauth_param_init(char *key, char *value)
{
    OAuthParameter *param = calloc(1, sizeof(OAuthParameter));
    param->key      = key;
    param->value    = value;
    return param;
}

void oauth_param_destroy(OAuthParameter *param)
{
    free(param->key);
    free(param->value);
    free(param);
}

void oauth_collection_add_params(OAuthParameterCollection* collection, char *data)
{
    char *input = strdup(data);
    for (char *token = strtok(input, "&"); token; token = strtok(NULL, "&")){
        char *p = strchr(token, '=');
        if (p != NULL){
            size_t pos = p-token;
            size_t value_len = strlen(token)-pos;
            size_t key_len = pos;
            char *key = calloc(key_len+1, sizeof(char));
            strncpy(key, token, pos);
            key[pos] = '\0';
            char *value = calloc(value_len+1, sizeof(char));
            strcpy(value, token+pos+1);

            char *unescaped = oauth_url_unescape(value, NULL);
            OAuthParameter *param = oauth_param_init(key, oauth_url_escape(unescaped));
            free(value);
            free(unescaped);
            collection->items[collection->count++] = param;
        }
    }
    free(input);
}

void oauth_collection_add_url_params(OAuthParameterCollection* collection, const char *url)
{
    char *p = strchr(url, '?');
    if (p == NULL){
        return;
    }
    int pos = (int)(p-url);
    size_t length = strlen(url)-pos;
    char *param_string = calloc(length+1, sizeof(char));
    strcpy(param_string, url+pos+1);
    oauth_collection_add_params(collection, param_string);
    free(param_string);
}


int oauth_compare_parameters(const void* a, const void*b)
{
    OAuthParameter **parameter1 = (OAuthParameter **)a;
    OAuthParameter **parameter2 = (OAuthParameter **)b;
    return strcmp((*parameter1)->key, (*parameter2)->key);
}


char *oauth_collection_join(OAuthParameterCollection* collection)
{
    char buffer[8192] = "\0";
    for (size_t i=0; i<collection->count; i++){
        OAuthParameter *param = collection->items[i];
        if (i > 0){
            strcat(buffer, "&");
        }
        strcat(buffer, param->key);
        strcat(buffer, "=");
        strcat(buffer, param->value);
    }
    return strdup(buffer);
}


int oauth_collection_param_key_exists(OAuthParameterCollection* collection, char *key)
{
    for (size_t i=0; i<collection->count; i++) {
        OAuthParameter *param = collection->items[i];
        if (strcmp(param->key, key) == 0){
            return 1;
        }
    }
    return 0;
}

char * oauth_get_base_url(char *url)
{
    char buffer[2048] = "\0";
    char *p;
    size_t pos;
    p = strchr(url, '?');
    if (p != NULL){
        pos = p-url;
        strncpy(buffer, url, pos);
        buffer[pos] = '\0';
    }
    else {
        strcpy(buffer, url);
    }
    return strdup(buffer);
}


char * oauth_sign_post(char *url, char *post_data, char *consumer_key, char *consumer_secret)
{
    char * base_url = oauth_get_base_url(url);
    char * encoded_base_url = oauth_url_escape(base_url);
    OAuthParameterCollection * collection = oauth_collection_init();
    oauth_collection_add_params(collection, post_data);
    oauth_collection_add_specific_params(collection, consumer_key);

    char *signed_post_body = oauth_collection_join(collection);

    oauth_collection_add_url_params(collection, url);
    oauth_collection_sort(collection);
    char * normalized_params = oauth_collection_join(collection);
    char * encoded_normalized_string = oauth_url_escape(normalized_params);

    char buffer[8192] = "POST&\0";
    strcat(buffer, encoded_base_url);
    strcat(buffer, "&");
    strcat(buffer, encoded_normalized_string);

    char *encoded_consumer_secret = oauth_url_escape(consumer_secret);
    char final_consumer_secret[128] = "\0";
    sprintf(final_consumer_secret, "%s&", encoded_consumer_secret);

    unsigned char *resbuf = calloc(128, sizeof(char));
    hmac_sha1(final_consumer_secret, strlen(final_consumer_secret), buffer, strlen(buffer), resbuf);

    char *signature = base64_encode(20, resbuf);
    char *encoded_signature = oauth_url_escape(signature);

    strcat(buffer, encoded_normalized_string);

    char final_signed_body[8192] = "\0";
    strcat(final_signed_body, signed_post_body);
    strcat(final_signed_body, "&oauth_signature=");
    strcat(final_signed_body, encoded_signature);

    free(signed_post_body);
    free(normalized_params);
    free(encoded_normalized_string);
    free(encoded_consumer_secret);
    free(resbuf);
    free(signature);
    free(encoded_signature);
    free(base_url);
    free(encoded_base_url);
    oauth_collection_destroy(collection);

    return strdup(final_signed_body);
}

char *oauth_gen_nonce(int len)
{
    char output[128] = "\0";
    int i;
    srand((unsigned int)time(NULL));
    static const char alphanum[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    for (i = 0; i < len; ++i) {
        output[i] = alphanum[rand() % (sizeof(alphanum) - 1)];
    }
    output[len] = '\0';
    return strdup(output);
    //return strdup("RKRIIT55Q6wsUtDHJkPFKAwalP8EGooo");
}

char * oauth_get_timestamp()
{
    char buffer[32] = "\0";
    sprintf(buffer, "%i", (size_t)time(NULL));
    return strdup(buffer);
    //return strdup("1522157348");
}


void oauth_collection_add_specific_params(OAuthParameterCollection *collection, char *consumer_key)
{
    if (!oauth_collection_param_key_exists(collection, "oauth_consumer_key")){
        collection->items[collection->count++] = oauth_param_init(strdup("oauth_consumer_key"), strdup(consumer_key));
    }
    if (!oauth_collection_param_key_exists(collection, "oauth_signature_method")){
        collection->items[collection->count++] = oauth_param_init(strdup("oauth_signature_method"), strdup("HMAC-SHA1"));
    }
    if (!oauth_collection_param_key_exists(collection, "oauth_version")){
        collection->items[collection->count++] = oauth_param_init(strdup("oauth_version"), strdup("1.0"));
    }
    collection->items[collection->count++] = oauth_param_init(strdup("oauth_nonce"), oauth_gen_nonce(32));
    collection->items[collection->count++] = oauth_param_init(strdup("oauth_timestamp"), oauth_get_timestamp());
}


void oauth_collection_sort(OAuthParameterCollection *collection)
{
    qsort(collection->items, collection->count, sizeof(OAuthParameter*), oauth_compare_parameters);
}


#ifndef ISXDIGIT
# define ISXDIGIT(x) (isxdigit((int) ((unsigned char)x)))
#endif

char *oauth_url_unescape(const char *string, size_t *olen)
{
    size_t alloc, strindex=0;
    char *ns = NULL;
    unsigned char in;
    long hex;
    if (!string) return NULL;
    alloc = strlen(string)+1;
    ns = (char*) calloc(alloc, sizeof(char));
    while(--alloc > 0) {
        in = *string;
        if(('%' == in) && ISXDIGIT(string[1]) && ISXDIGIT(string[2])) {
            char hexstr[3]; // '%XX'
            hexstr[0] = string[1];
            hexstr[1] = string[2];
            hexstr[2] = 0;
            hex = strtol(hexstr, NULL, 16);
            in = (unsigned char)hex; /* hex is always < 256 */
            string+=2;
            alloc-=2;
        }
        ns[strindex++] = in;
        string++;
    }
    ns[strindex]=0;
    if(olen) *olen = strindex;
    return ns;
}


char *oauth_url_escape(const char *string)
{
    size_t alloc, newlen;
    char *ns = NULL, *testing_ptr = NULL;
    unsigned char in;
    size_t strindex=0;
    size_t length;
    if (!string) return NULL;
    alloc = strlen(string)+1;
    newlen = alloc;
    ns = (char*) calloc(alloc, sizeof(char));
    length = alloc-1;
    while(length--) {
        in = *string;
        switch(in){
            case '0': case '1': case '2': case '3': case '4':
            case '5': case '6': case '7': case '8': case '9':
            case 'a': case 'b': case 'c': case 'd': case 'e':
            case 'f': case 'g': case 'h': case 'i': case 'j':
            case 'k': case 'l': case 'm': case 'n': case 'o':
            case 'p': case 'q': case 'r': case 's': case 't':
            case 'u': case 'v': case 'w': case 'x': case 'y': case 'z':
            case 'A': case 'B': case 'C': case 'D': case 'E':
            case 'F': case 'G': case 'H': case 'I': case 'J':
            case 'K': case 'L': case 'M': case 'N': case 'O':
            case 'P': case 'Q': case 'R': case 'S': case 'T':
            case 'U': case 'V': case 'W': case 'X': case 'Y': case 'Z':
            case '_': case '~': case '.': case '-':
                ns[strindex++]=in;
                break;
            default:
                newlen += 2; /* this'll become a %XX */
                if(newlen > alloc) {
                    alloc *= 2;
                    testing_ptr = (char*) realloc(ns, alloc);
                    ns = testing_ptr;
                }
                snprintf(&ns[strindex], 4, "%%%02X", in);
                strindex+=3;
                break;
        }
        string++;
    }
    ns[strindex]=0;
    return ns;
}