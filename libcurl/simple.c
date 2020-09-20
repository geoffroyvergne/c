#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int main(void) {
    CURL *curl;
    CURLcode res;

    curl = curl_easy_init();

    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://www.google.fr");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

        res = curl_easy_perform(curl);

        if(CURLE_OK == res) {
            
        } else {
            fprintf(stderr, "curl_easy_perform() failed: %s n", curl_easy_strerror(res));

        }

        curl_easy_cleanup(curl);
    }

    return EXIT_SUCCESS;
}