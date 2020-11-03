#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>

#include <ini-mgr.h>
#include <cli.h>
#include <config.h>
#include <main.h>
#include <file.h>
#include <tcp-server.h>

void printConfig(config conf) {    
    printf("Config : port=%d, host=%s, target=%s\n", conf.port, conf.host, conf.target);
}

int main(int argc, char **argv) {

    setbuf(stdout, NULL);  

    // get config from cli
    config conf = getOptions(argc, argv);
    //char* confFile = conf.file;

    //size_t len = strlen(conf.file);

    // if cli file provided get ini config
    if(strlen(conf.file) > 0) {
        conf = getIniConfig(conf.file);
        printConfig(conf);
    }

    printf("Start http-server host : %s port : %i\n", conf.host, conf.port);

    // start server socket
    tcp_connect(conf.port, conf.host, conf.target);
    tcp_shutdown();

    return EXIT_SUCCESS;
}
