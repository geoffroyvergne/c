
#ifndef HTTP
#define HTTP

static const char* GET = "get";
static const char* POST = "post";
static const char* PUT = "put";
static const char* DELETE = "delete";
static const char* OPTION = "option";
static const char* PATCH = "patch";

static const char* HTTP_VERB_LIST[] = {"get", "post", "put", "delete", "option", "patch"};
static const char* HTTP_HEADER_LIST[] = {"host", "user-agent", "accept"};
static const char* INDEX_HTML_LIST[] = {"index.htm", "index.html"};

struct header {
    char* host;
    char* user_agent;
    char* accept;
};

struct http {
    char* verb;
    char* path;
    char* protocol;
    unsigned int status_code;
    char* status_reason;
    char* content_type;
};

struct http_header {
    struct header* header;
    struct http* http;
};

struct http *extract_first_line_header(char *line, char *separator);
struct http_header* extract_headers(char *lines, char *separator);
char* getContentType(char* uri);

#endif
