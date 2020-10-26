
int tcp_shutdown();
int tcp_connect();

void *connection_handler(void *);
//void sig_handler(int signo);
void *connection_handler(void *socket_desc);

char* getHelp();
