#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#include <cli.h>
#include <main.h>
#include <file.h>
#include <tcp-server.h>

int main(int argc, char **argv) {

    struct config conf = getOptions(argc, argv);

    tcp_connect(conf.port, conf.target, "127.0.0.1");
    tcp_shutdown();

    return EXIT_SUCCESS;
}
