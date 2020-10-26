//#include <http.h>

int tcp_connect(int port, char* target, char* host);
int tcp_shutdown();
//void *connection_handler(void *);
void *connection_handler(void* params);
void write_message(char *content, int *sock);
char* create_message(char *message, char* http_code, char *http_reason);
//char* parseHeader(char* client_message);
//void tcp_log(struct http_header* http_header);