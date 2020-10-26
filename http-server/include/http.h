
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

struct http extract_first_line_header(char *line, char *separator);
struct http_header extract_headers(char *lines, char *separator);
