#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <ssl-server.h>

#ifndef TCPSEVER
#define TCPSERVE

int tcp_connect(int port);
void handle_connection(int socket, SSL_CTX *ctx);

char* getHelp();

#endif
