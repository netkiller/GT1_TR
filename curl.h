#include <curl/curl.h>

struct string {
  char *ptr;
  size_t len;
};

void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s)
{
  size_t new_len = s->len + size*nmemb;
  s->ptr = realloc(s->ptr, new_len+1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr+s->len, ptr, size*nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size*nmemb;
}

char * conn(char *host, char *protocol)
{
	CURL *curl;
	CURLcode res;
	char *rev;
	char *url = NULL;
	curl = curl_easy_init();
	if(curl) {
		struct string s;
		init_string(&s);

		asprintf(&url, "%s?%s",host, curl_easy_escape(curl, protocol, 0));
		//printf("url: %s\n", url);
		
		curl_easy_setopt(curl, CURLOPT_URL, url);
		curl_easy_setopt(curl, CURLOPT_USERAGENT, "netkiller <netkiller@msn.com>");
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
	 
		/* Perform the request, res will get the return code */ 
		res = curl_easy_perform(curl);
		/* Check for errors */ 
		if(res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",	curl_easy_strerror(res));

		asprintf(&rev, "%s", s.ptr);
		
		free(s.ptr);
		
		/* always cleanup */ 
		curl_easy_cleanup(curl);
	}
	return rev;
}