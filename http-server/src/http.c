#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#include <string-utils.h>
#include <http.h>

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

struct http extract_first_line_header(char *line, char *separator) {
    char* token_line;
    char* rest_line = line;
    char* value;
    struct http http;

    while ((token_line = strtok_r(rest_line, separator, &rest_line))) {

        value = toLowerCase(token_line);

        if(isValidVerb(value)) {
            http.verb = token_line;
        } else if(strstr(value, "http/")) {
            http.protocol = token_line;
        } else {
            http.path = token_line;
        }
    }

    return http;
}

struct http_header extract_headers(char *lines, char *separator) {  

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

    struct header header;
    struct http http;
    struct http_header http_header;

    while ((token_line = strtok_r(rest_line, separator, &rest_line))) {        

        // if it is the first line extract verb path and protocol
        if(i==0) http = extract_first_line_header(token_line, " ");

        // and extract http standards headers
        token_line = toLowerCase(token_line);
        
        key = "host";
        if(strstr(token_line, key)) {
            header.host = substr(token_line, (strlen(key)+2), strlen(token_line));
        }

        key = "user-agent";
        if(strstr(token_line, key)) {
            header.user_agent = substr(token_line, (strlen(key)+2), strlen(token_line));
        }

        key = "accept";
        if(strstr(token_line, key)) {
            header.accept = substr(token_line, (strlen(key)+2), strlen(token_line));
        }      

        i++;  
    }

    //http.status_code = "200";

    http_header.header = header;
    http_header.http = http;

    return http_header;
}
