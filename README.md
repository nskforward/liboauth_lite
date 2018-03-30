# liboauth_lite
Light implementation of OAuth 1.0 (rfc5849) using C language without OpenSSL

### How to install
- git clone https://github.com/nskforward/liboauth_lite.git
- Install Windows gcc (http://www.mingw.org/)

### How to compile DLL library
- By CLion IDE: click "Run"->"Build" (Ctrl+F9)
- By MinGW terminal execute:
```
gcc -m32 -shared -static-libgcc -o liboauth_lite.dll library.c library.h src/oauth.c src/oauth.h src/sha1.c src/sha1.h src/memxor.c src/memxor.h src/base64.c src/base64.h src/xmalloc.c src/xmalloc.h
```

### How use DLL in Loadrunner script
- Attach *distr/liboauth_lite.dll* and *distr/oauth.h* files to your script folder
- Include the load instruction to the **vuser_init** action of script before function signature
```
#include "oauth.h"
```
- Include below instruction inside vuser_init action
 ```
 lr_load_dll("liboauth_lite.dll");
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
  "{Host}/?service=lti&method=launch",
  "Snapshot=t1.inf",
  "Body={OAUTH_SIGNED_BODY}",
  LAST);
```
**OAUTH_SIGNED_BODY** is newly created variable by liboauth_lite 

### Functions
- void **oauth_sign_body**(char *oauth_consumer_key, char *oauth_consumer_secret, char *http_method, char *http_url, char *http_post_body, char * out_body);
- void **oauth_sign_header**(char *oauth_consumer_key, char *oauth_consumer_secret, char *http_method, char *http_url, char *http_post_body, char *out_header);

### Compiled x86 DLL
https://github.com/nskforward/liboauth_lite/blob/master/distr/liboauth_lite.dll