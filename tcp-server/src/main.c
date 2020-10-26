#include <stdio.h>
#include <stdlib.h>

#include <cli.h>
#include <tcp-server.h>
#include <main.h>

int main(int argc, char **argv) {

    struct config conf = getOptions(argc, argv);
    //printf("port : %i\n", conf.port);

    tcp_connect(conf.port);
    tcp_shutdown();

    return EXIT_SUCCESS;
}
