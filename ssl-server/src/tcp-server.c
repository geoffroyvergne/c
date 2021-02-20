#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#include <tcp-server.h>
#include <ssl-server.h>

struct sockaddr_in server;

char* getHelp() {
    return "Avaliable commands : ping quit help \n";
    exit(EXIT_SUCCESS);
}

int tcp_connect(int port) {
    int socket_desc;

    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    
    //addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc < 0) {
	    perror("Unable to create socket");
	    exit(EXIT_FAILURE);
    }

    if (bind(socket_desc, (struct sockaddr*)&server, sizeof(server)) < 0) {
	    perror("Unable to bind");
	    exit(EXIT_FAILURE);
    }

    if (listen(socket_desc, 1) < 0) {
	    perror("Unable to listen");
	    exit(EXIT_FAILURE);
    }

    return socket_desc;
}

void handle_connection(int socket, SSL_CTX *ctx) {
    while(1) {
        struct sockaddr_in addr;
        uint len = sizeof(addr);
        SSL *ssl;
        const char reply[] = "SSL server test\n";

        int client = accept(socket, (struct sockaddr*)&addr, &len);
        if (client < 0) {
            perror("Unable to accept");
            exit(EXIT_FAILURE);
        }

        ssl = SSL_new(ctx);
        SSL_set_fd(ssl, client);

        if (SSL_accept(ssl) <= 0) {
            ERR_print_errors_fp(stderr);
        }
        else {
            SSL_write(ssl, reply, strlen(reply));
        }

        SSL_shutdown(ssl);
        SSL_free(ssl);
        close(client);
    }
}