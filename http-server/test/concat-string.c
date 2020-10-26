#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct header {
    char* host;
    char* user_agent;
    char* accept;
};

struct http {
    char* verb;
    char* path;
    char* protocol;
    char* status_code;
};

struct http_header {
    struct header header;
    struct http http;
};

void tcp_log(struct http_header* http_header) {
    char *log = (char *) malloc( sizeof(char) * 2000 );
    strncat(log, http_header->http.verb, strlen(http_header->http.verb));
    strncat(log, " ", 1);
    strncat(log, http_header->http.path, strlen(http_header->http.path));
    strncat(log, " ", 1);
    strncat(log, http_header->http.protocol, strlen(http_header->http.protocol));
    strncat(log, " ", 1);
    strncat(log, http_header->http.status_code, strlen(http_header->http.status_code));
    strncat(log, " ", 1);

    puts(log);
    free(log);
}

int main() {
    puts("log");

    char *verb = "get";
    char *protocol = "HTTP/1.0";
    char *status_code = "200";
    char *path = "/";

    struct http http;
    struct http_header http_header;

    http.verb = verb;
    http.protocol = protocol;
    http.status_code = status_code;
    http.path = path;

    http_header.http = http;

     tcp_log(&http_header);

    return 0;
}
