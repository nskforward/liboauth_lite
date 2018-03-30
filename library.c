//
// Created by ishibkikh on 3/30/2018.
//

#include "library.h"

void oauth_sign_body(char *oauth_consumer_key, char *oauth_consumer_secret, char *http_method, char *http_url, char *http_post_body, char * out_body)
{
    if (strcmp(http_method, "POST") != 0){
        printf("%s http method is not supported. Please create a new issue here https://github.com/nskforward/liboauth_lite/issues", http_method);
        return;
    }
    out_body = oauth_sign_post(http_url, http_post_body, oauth_consumer_key, oauth_consumer_secret);
}