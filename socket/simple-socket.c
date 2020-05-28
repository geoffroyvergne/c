#include <stdio.h>
#include <sys/socket.h>

int main (int argc, char **argv) {
    int socket_desk;
    socket_desk = socket(AF_INET, SOCK_STREAM, 0);

    if (socket_desk == 1) {
        printf("Couldn't create socket");
    }

    return 0;
}