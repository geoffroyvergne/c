#include <stdio.h>
#include <string.h>
#include <ctype.h>
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
};

struct http_header {
    struct header header;
    struct http http;
};

char *ltrim(char *s) {
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s) {
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s) {
    return rtrim(ltrim(s)); 
}

char* toLowerCase(char* s) {
  for(char *p=s; *p; p++) *p=tolower(*p);
  return s;
}

char* toUpperCase(char* s) {
  for(char *p=s; *p; p++) *p=toupper(*p);
  return s;
}

char* substr(const char *src, int m, int n) {
	// get length of the destination string
	int len = n - m;

	// allocate (len + 1) chars for destination (+1 for extra null character)
	char *dest = (char*)malloc(sizeof(char) * (len + 1));

	// extracts characters between m'th and n'th index from source string
	// and copy them into the destination string
	for (int i = m; i < n && (*(src + i) != '\0'); i++)
	{
		*dest = *(src + i);
		dest++;
	}

	// null-terminate the destination string
	*dest = '\0';

	// return the destination string
	return dest - len;
}

/*void extract_strtok(char *lines, char *separator) {    
    char *token;
    token = strtok(lines, separator);

    int i=0;
    while (token != NULL) {
        printf("%d: [%s]\n", ++i, token);
        token = strtok(NULL, separator);
    }
}*/

struct http extract_first_line_header(char *line, char *separator) {
    char* token_line;
    char* rest_line = line;
    char* key;

    struct http http;

    while ((token_line = strtok_r(rest_line, separator, &rest_line))) {
        //printf("'%s'\n", token_line);
        
        if(strstr(toLowerCase(token_line), "get")) {
            //printf("'verb' : '%s'\n", token_line);
            http.verb = token_line;
        } else if(strstr(toLowerCase(token_line), "http/")) {
            //printf("'protocol' : '%s'\n", token_line);
            http.protocol = token_line;
        } else {
            //printf("'path' : '%s'\n", token_line);
            http.path = token_line;
        }
    }

    //token_line = strtok_r(rest_line, separator, &rest_line);
    //printf("'%s' ", token_line);

    return http;
}

struct http_header extract_headers(char *lines, char *separator) {   
    char* token_line;
    char* rest_line = lines;
    char* key;
    int i=0;

    struct header header;
    struct http http;
    struct http_header http_header;

    while ((token_line = strtok_r(rest_line, separator, &rest_line))) {        

        /*key = "get";
        if(strstr(toLowerCase(token_line), key)) {
            extract_first_line_header(token_line, " ");
        }*/

        if(i==0) {
            http = extract_first_line_header(token_line, " ");
        }

        token_line = toLowerCase(token_line);
        
        key = "host";
        if(strstr(token_line, key)) {
            //printf("'host' : '%s'\n", substr(token_line, (strlen(key)+2), strlen(token_line)));
            header.host = substr(token_line, (strlen(key)+2), strlen(token_line));
        }

        key = "user-agent";
        if(strstr(token_line, key)) {
            //printf("'user-agent' : '%s'\n", substr(token_line, (strlen(key)+2), strlen(token_line)));
            header.user_agent = substr(token_line, (strlen(key)+2), strlen(token_line));
        }

        key = "accept";
        if(strstr(token_line, key)) {
            //printf("'accept' : '%s'\n", substr(token_line, (strlen(key)+2), strlen(token_line)));
            header.accept = substr(token_line, (strlen(key)+2), strlen(token_line));
        }      

        i++;  
    }

    http_header.header = header;
    http_header.http = http;

    return http_header;
}

int main() {
    char lines[] = "GET / HTTP/1.1\nHost: localhost:8888\nUser-Agent: curl/7.70.0\nAccept: *\n\n";
    //char lines[] = "Host: localhost:8888\nUser-Agent: curl/7.70.0\nAccept: *\n\n";
    //char line[] = "Host: localhost:8888";

    printf("%s", lines);

    printf("%s", trim(lines));

    //extract_strtok(lines, "\n");
    struct http_header http_header = extract_headers(lines, "\n");

    printf("'verb' : '%s'\n", http_header.http.verb);
    printf("'protocol' : '%s'\n", http_header.http.protocol);
    printf("'path' : '%s'\n", http_header.http.path);

    printf("'host' : '%s'\n", http_header.header.host);
    printf("'user-agent' : '%s'\n", http_header.header.user_agent);
    printf("'accept' : '%s'\n", http_header.header.accept);
    
    return 0;
}
