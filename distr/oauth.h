lr_load_dll("liboauth_lite.dll");

/*
    @Return:
	    OAUTH_URL          - LoadRunner output var
	    OAUTH_SIGNED_BODY  - LoadRunner output var
*/
void oauth_sign_post(char* http_method,
                     char* url,
                     char* http_post_body,
                     char* consumer_key,
                     char* consumer_secret)
{
    char out_body[3200];
    lr_save_string(lr_eval_string(url), "OAUTH_URL");
    lr_save_string(lr_eval_string(http_post_body), "OAUTH_PARAMETERS");
    oauth_sign_body(consumer_key, consumer_secret, http_method, lr_eval_string("{OAUTH_URL}"), lr_eval_string("{OAUTH_PARAMETERS}"), out_body);
    lr_save_string(out_body, "OAUTH_SIGNED_BODY");
    free(out_body);
}