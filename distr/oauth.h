/*
 * https://github.com/nskforward/liboauth_lite
 */


/*
    @Return:
	    OAUTH_URL          - LoadRunner output var
	    OAUTH_SIGNED_BODY  - LoadRunner output var
*/
void oauth_sign_body(char *oauth_consumer_key, char *oauth_consumer_secret, char *http_method, char *http_url, char *http_post_body, void *out_body);

void lr_oauth_sign_request(char* http_method,
                           char* url,
                           char* http_post_body,
                           char* consumer_key,
                           char* consumer_secret)
{
    char out_body[8192] = "\0";
    oauth_sign_body(consumer_key, consumer_secret, http_method, url, http_post_body, &out_body);
    lr_save_string(out_body, "OAUTH_SIGNED_BODY");
}