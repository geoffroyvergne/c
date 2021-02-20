#include <openssl/ssl.h>
#include <openssl/err.h>

#ifndef SSLSERVER
#define SSLSERVER

void init_openssl();
void cleanup_openssl();
SSL_CTX *create_context();
void configure_context(SSL_CTX *ctx);

#endif