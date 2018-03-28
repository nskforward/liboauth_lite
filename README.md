# liboauth_lite
Light implementation of OAuth 1.0 (rfc5849) using C language

### How to install
- git clone https://github.com/nskforward/liboauth_lite.git
- Install Windows gcc (http://www.mingw.org/)

### How to compile DLL library
- By CLion IDE: click "Run"->"Build" (Ctrl+F9)
- By MinGW terminal execute:
```
gcc -m32 -shared -o liboauth_lite.dll oauth.c collection.c oauth-tools.c hmac-sha1.c sha1.c memxor.c
```

### How use DLL in Loadrunner script
- Attach *liboauth_lite.dll* and *oauth.h* files to your script folder
- Include the load instruction to the **vuser_init** action of script
```
#include "oauth.h"
lr_load_dll("myoauth.dll");
```

### Example
```
oauth_sign_post(
  "POST",
  "{Host}/?service=lti&method=launch",
  "context_id={ContextId}&context_label={ContextLabel}",
  "consumer_key",
  "consumer_secret"
  );
	
web_custom_request("request",
  "Method=POST",
  "URL={OAUTH_URL}",
  "Snapshot=t1.inf",
  "Body={OAUTH_SIGNED_BODY}",
  LAST);
```
**OAUTH_URL** and **OAUTH_SIGNED_BODY** are newly created variables by liboauth_lite 

### Functions
- void **oauth_sign_body**(char *oauth_consumer_key, char *oauth_consumer_secret, char *http_method, char *http_url, char *http_post_body, char * out_body);
- void **oauth_sign_header**(char *oauth_consumer_key, char *oauth_consumer_secret, char *http_method, char *http_url, char *http_post_body, char *out_header);

### Compiled x86 DLL
https://github.com/nskforward/oauth_c/tree/master/dist