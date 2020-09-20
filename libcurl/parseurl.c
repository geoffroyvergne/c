#include <stdio.h>
#include <curl/curl.h>

#include <stdlib.h>

#if !CURL_AT_LEAST_VERSION(7, 62, 0)
#error "this example requires curl 7.62.0 or later"
#endif

void fail(CURL *h);

int main() {
    CURL *h;
    CURLUcode uc;

    char *host;
    char *path;

    h = curl_url();
    if(!h) return 1;

    // parse a full URL
    uc = curl_url_set(h, CURLUPART_URL, "https://www.google.fr", 0);
    if(uc) fail(&h);

    // extract hostname from the parse url
    uc = curl_url_get(h, CURLUPART_HOST, &host, 0);
    if(!uc) {
        printf("Host name : %s \n", host);
        curl_free(host);
    }

    // extract path from the parse url
    uc = curl_url_get(h, CURLUPART_PATH, &path, 0);
    if(!uc) {
        printf("Path : %s \n", path);
        curl_free(path);
    }

    return 0;
}

void fail(CURL *h) {
    curl_url_cleanup(h); /* free url handle */
    EXIT_FAILURE;
}
