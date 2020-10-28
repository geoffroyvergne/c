#include <http.h>

#ifndef TCP_SERVER
#define TCP_SERVER

int tcp_connect(int port, char* target, char* host);
int tcp_shutdown();
void *connection_handler(void* params);
char* create_message(char *message, struct http_header* http_header);

#endif