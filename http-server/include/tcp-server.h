//#include <http.h>

int tcp_connect(int port, char* target, char* host);
int tcp_shutdown();
void *connection_handler(void* params);
char* create_message(char *message, char* http_code, char *http_reason);
