#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include <string-utils.h>
#include <http.h>

char* getContentType(char* uri) {
    if(strstr(uri, ".txt")) return "application/text";
    //if(strstr(uri, ".htm")) return "text/htm";
    if(strstr(uri, ".html")) return "text/html";

    if(strstr(uri, ".css")) return "text/css";
    if(strstr(uri, ".js")) return "application/javascript";

    if(strstr(uri, ".png")) return "image/png";
    if(strstr(uri, ".jpg")) return "image/jpeg";
    if(strstr(uri, ".gif")) return "image/gif";
    if(strstr(uri, ".svg")) return "image/svg+xml";

    return NULL;
}

int isBinary(char* uri) {
    if(strstr(uri, ".txt")) return 0;
    //if(strstr(uri, ".htm")) return 0;
    if(strstr(uri, ".html")) return 0;

    if(strstr(uri, ".css")) return 0;
    if(strstr(uri, ".js")) return 0;

    if(strstr(uri, ".png")) return 1;
    if(strstr(uri, ".jpg")) return 1;
    if(strstr(uri, ".gif")) return 1;
    if(strstr(uri, ".svg")) return 0;

    return 0;
}

// Check if string contains a valid http verb
int isValidVerb(char * value) {
    int validVerb = 0;

    size_t i = 0;
    for( i = 0; i < sizeof(HTTP_VERB_LIST) / sizeof(HTTP_VERB_LIST[0]); i++) {
        if(strcmp (value, HTTP_VERB_LIST[i]) == 0) {
            validVerb = 1;
            break;
        }
    }

    return validVerb;
}

struct http* extract_first_line_header(char *line, char *separator) {
    char* token_line;
    char* rest_line = line;
    char* value;
    struct http* http;
    http = (struct http*) malloc(sizeof(struct http));

    while ((token_line = strtok_r(rest_line, separator, &rest_line))) {

        value = toLowerCase(token_line);

        if(isValidVerb(value)) {
            http->verb = token_line;
        } else if(strstr(value, "http/")) {
            http->protocol = substr(token_line, 0, (strlen(token_line) -1));
        } else {
            http->path = token_line;
        }
    }

    /*if(strcmp(http->path, "/") == 0) {
        strcat(http->path, "index.html");
    }*/

    return http;
}

struct http_header* extract_headers(char *lines, char *separator) {  

    // GET / HTTP/1.0 <CRLF><CRLF>
    /*
    GET / HTTP/1.1
    Host: localhost:8888
    User-Agent: curl/7.70.0
    Accept: *
    */

    char* token_line;
    char* rest_line = lines;
    char* key;
    int i=0;

    struct header* header;
    header = (struct header*) malloc(sizeof(struct header));

    struct http *http;
    http = (struct http*) malloc(sizeof(struct http));

    struct http_header *http_header;
    http_header = (struct http_header*) malloc(sizeof(struct http_header));

    while ((token_line = strtok_r(rest_line, separator, &rest_line))) {        

        // if it is the first line extract verb path and protocol
        if(i==0) http = extract_first_line_header(token_line, " ");

        // and extract http standards headers
        token_line = toLowerCase(token_line);

        //puts(token_line);

        // iterate over headers to extract them
        /*size_t j = 0;
        for( j = 0; j < sizeof(HTTP_HEADER_LIST) / sizeof(HTTP_HEADER_LIST[0]); j++) {
            //key = HTTP_HEADER_LIST[j];
            if(strstr(token_line, HTTP_HEADER_LIST[j])) {
                header->host = substr(token_line, (strlen(HTTP_HEADER_LIST[j])+2), (strlen(token_line) -1));
            }

            //puts(HTTP_HEADER_LIST[j]);
        }*/
        
        // TODO debug results
        key = "host";
        if(strstr(token_line, key)) {
            header->host = substr(token_line, (strlen(key)+2), (strlen(token_line) -1));
            header->host = "";
            //printf("header host : %s\n", header->host);
        }

        key = "user-agent";
        if(strstr(token_line, key)) {
            //header->user_agent = substr(token_line, (strlen(key)+2), strlen(token_line) -1);
            header->user_agent = "";
        }

        key = "accept";
        if(strstr(token_line, key)) {
            //header->accept = substr(token_line, (strlen(key)+2), strlen(token_line) -1);
            header->accept = "";
        }

        i++;  
    }

    http_header->header = header;
    http_header->http = http;

    return http_header;
}
