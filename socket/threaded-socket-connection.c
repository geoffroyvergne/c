#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include<unistd.h>
#include<pthread.h>
#include<signal.h>

void *connection_handler(void *);

void sig_handler(int signo) {
  if (signo == SIGINT) {
    printf("received SIGINT\n");

    exit(0);
    //abort();
  }
}

int main(int argc, char **argv) {

    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        printf("\ncan't catch SIGINT\n");
    }

    int socket_desc, new_socket, c, *new_sock;
    struct sockaddr_in server, client;
    char *message;

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_desc == -1) {
        printf("Could not create socket\n");
    }

    // Prepare sockaddr_in structure
    //server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(8888);
   
    if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) ==- 1) {
        puts("bind failed\n");
        return 1;
    }
    puts("bind done\n");

    // Listen socket
    listen(socket_desc , 3);

    // Accept incomming connections
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    while ((new_socket = accept(socket_desc, (struct sockaddr *) &client, (socklen_t *) &c))) {
        puts("Connection accepted\n");

        //char *client_ip = inet_ntoa(client.sin_addr);
        message = "Hello Client\n";
        write(new_socket, message, strlen(message));

        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = new_socket;

        if(pthread_create(&sniffer_thread, NULL, connection_handler, (void*) new_sock) == -1) {
            perror("couldn't create thread\n");
            return 1;
        }

        puts("Handler assigned\n");
    }
    
    if( (new_socket < 0) ) {
        perror("accept failed\n");
    } 

    close(socket_desc);
    close(new_socket);
    pthread_exit(NULL);
    return 0;
}

void *connection_handler(void *socket_desc) {
    int sock = *(int*) socket_desc;
    int read_size;
    char *message, client_message[2000];

    message = "Greeting from connection handler type quit to leave\n";
    write(sock, message, strlen(message));

    message = "Connection opened\n";
    write(sock, message, strlen(message));

    //Recieve message from client
    while((read_size = recv(sock, client_message, 2000, 0)) > 0) {
        //Send message back to client
        //replyMessage = "Message recieved";
        //write(sock, replyMessage, strlen(replyMessage));

        printf("Client message : %s", client_message);
        //char quitMessage[] = "quit";

        //printf("strcmp result : %i\n", strcmp(client_message, quitMessage));

        /*if(strncmp(client_message, quitMessage, 4) == 0) {
            puts("quit detected\n");
            //free(socket_desc);
            break;
            //return 0;
        }*/

        memset(client_message, 0, 2000);
    }

    if(read_size == 0) {
        puts("Client disconnected\n");
        fflush(stdout);
    } else {
        perror("recv failed\n");
    }

    free(socket_desc);
    //pthread_cancel(socket_desc);
    pthread_exit(NULL);

    return 0;
}