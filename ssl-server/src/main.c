#include <stdio.h>
#include <unistd.h>

#include <tcp-server.h>
#include <ssl-server.h>

int main(int argc, char **argv) {
    int socket;
    SSL_CTX *ctx;

    // SSL
    init_openssl();
    ctx = create_context();

    configure_context(ctx);

    // Socket
    socket = tcp_connect(3000);
    handle_connection(socket, ctx);

    // Free
    close(socket);
    SSL_CTX_free(ctx);
    cleanup_openssl();
}
