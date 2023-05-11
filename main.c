#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct memory
{
    char* response;
    size_t size;
};

static size_t cb(void* data, size_t size, size_t nmemb, void* clientp)
{
    size_t realsize    = size * nmemb;
    struct memory* mem = (struct memory*)clientp;

    char* ptr = realloc(mem->response, mem->size + realsize + 1);
    if (ptr == NULL)
        return 0; /* out of memory! */

    mem->response = ptr;
    memcpy(&(mem->response[mem->size]), data, realsize);
    mem->size += realsize;
    mem->response[mem->size] = 0;

    return realsize;
};

// Useful examples:
// https://curl.se/libcurl/c/https.html
// https://curl.se/libcurl/c/CURLOPT_WRITEFUNCTION.html
int main()
{
    CURLcode res;
    struct memory chunk = {0};
    CURL* curl_handle   = curl_easy_init();
    long http_code      = 0;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    if (curl_handle)
    {
        /* send all data to this function  */
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, cb);

        /* we pass our 'chunk' struct to the callback function */
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void*)&chunk);

        curl_easy_setopt(curl_handle, CURLOPT_URL, "https://example.com/");

        /* send a request */
        res = curl_easy_perform(curl_handle);

        curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &http_code);

        printf("HTTP Code: %ld\n", http_code);
        printf("Response length: %lu\n", chunk.size);
        printf("Response: %s\n", chunk.response);

        /* remember to free the buffer */
        free(chunk.response);

        curl_easy_cleanup(curl_handle);
    }

    curl_global_cleanup();

    return 0;
}
