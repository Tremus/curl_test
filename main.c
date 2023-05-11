#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct https_response
{
    char* body;
    size_t size;
    long status;
};

static size_t https_request_cb(void* data, size_t size, size_t nmemb,
                               void* clientp)
{
    size_t realsize            = size * nmemb;
    struct https_response* mem = (struct https_response*)clientp;

    char* ptr = realloc(mem->body, mem->size + realsize + 1);
    if (ptr == NULL)
        return 0; /* out of memory! */

    mem->body = ptr;
    memcpy(&(mem->body[mem->size]), data, realsize);
    mem->size += realsize;
    mem->body[mem->size] = 0;

    return realsize;
};

// Use this for simple GET requests
static CURLcode https_get(CURL* session, struct https_response* res,
                          const char* url)
{
    /* send all data to this function  */
    curl_easy_setopt(session, CURLOPT_WRITEFUNCTION, https_request_cb);

    /* we pass our 'https_response' struct to the callback function */
    curl_easy_setopt(session, CURLOPT_WRITEDATA, (void*)res);

    curl_easy_setopt(session, CURLOPT_URL, url);

    /* send a request */
    CURLcode code = curl_easy_perform(session);

    curl_easy_getinfo(session, CURLINFO_RESPONSE_CODE, &res->status);
    return code;
}

// Useful examples:
// https://curl.se/libcurl/c/https.html
// https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
int main()
{
    CURLcode code;
    struct https_response res = {0, 0, 0};
    CURL* session             = curl_easy_init();

    curl_global_init(CURL_GLOBAL_DEFAULT);

    if (session)
    {
        code = https_get(session, &res, "https://example.com/");

        if (code == CURLE_OK)
        {
            printf("HTTP Status: %ld\n", res.status);
            printf("Response length: %llu\n", res.size);
            printf("Response: %s\n", res.body);
        }
        else
        {
            fprintf(stderr, "curl_easy_perform() failed: %s\n",
                    curl_easy_strerror(code));
        }

        /* remember to free the buffer */
        free(res.body);
        curl_easy_cleanup(session);
    }

    curl_global_cleanup();

    return 0;
}
