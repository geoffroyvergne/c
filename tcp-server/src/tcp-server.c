#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>
#include <netinet/in.h>
#include <tcp-server.h>
#include <main.h>
#include <cli.h>

void sig_handler(int signo);

int socket_desc, new_socket, sockaddr_in_size, *new_sock;
struct sockaddr_in server, client;
char *message;
char *client_message;

char* getHelp() {
    return "Avaliable commands : ping quit help \n";
    exit(EXIT_SUCCESS);
}

int tcp_connect(int port) {
    printf("Start tcp-server port : %i\n", port);

    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        printf("\ncan't catch SIGINT\n");
    }

     // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_desc == -1) {
        printf("Could not create socket\n");
    }

    // Prepare sockaddr_in structure
    //server.sin_addr.s_addr = inet_addr("127.0.0.1");
    //server.sin_addr.s_addr = INADDR_LOOPBACK;
    
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    //true = 1;
    //setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&true,sizeof(int))

    if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) {
        puts("setsockopt(SO_REUSEADDR) failed");
    }
   
    if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) ==- 1) {
        puts("bind failed\n");
        return 1;
    }
    //puts("bind done\n");

    // Listen socket
    listen(socket_desc , 3);

    // Accept incomming connections
    puts("Waiting for incoming connections...");
    sockaddr_in_size = sizeof(struct sockaddr_in);
    while ((new_socket = accept(socket_desc, (struct sockaddr *) &client, (socklen_t *) &sockaddr_in_size))) {
        puts("Connection accepted");

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

        //puts("Handler assigned\n");
    }
    
    if( (new_socket < 0) ) {
        perror("accept failed\n");
    } 

    return 0;
}

int tcp_shutdown() {
    shutdown(socket_desc, 2);
    shutdown(new_socket, 2);
    pthread_exit(NULL);
}

void *connection_handler(void *socket_desc) {
    int sock = *(int*) socket_desc;
    int read_size;
   
    //char client_message[2000];
    client_message = (char *) malloc( 2000 );
    message = (char *) malloc( 2000 );

    strcpy(message, "Welcome! \n");
    write(sock, message, strlen(message));

    write(sock, getHelp(), strlen(getHelp()));

    //strcpy(message, "Connection opened\n");
    //puts(message);

    while((read_size = recv(sock, client_message, 2000, 0)) > 0) {
        
        if(strlen(client_message) > 2) {
            if(strncmp(client_message, "quit", 4) == 0) {
                strcpy(message, "bye!\n");
                puts("Client leaved !");
                write(sock, message, strlen(message));

                break;
            } else if(strncmp(client_message, "ping", 4) == 0) {            
                strcpy(message, "pong\n");
                puts("pong");
                write(sock, message, strlen(message));
            } else if (strncmp(client_message, "help", 4) == 0) {
                write(sock, getHelp(), strlen(getHelp()));
            } else {            
                strcpy(message, "Unknown message : ");
                strcat(message, client_message);
                puts("Unknown message");

                write(sock, message, strlen(message));
            }
        }

        memset(client_message, 0, 2000);
    }

    /*if(read_size == 0) {
        puts("Client disconnected\n");
        fflush(stdout);
    } else {
        perror("recv failed\n");
    }*/

    close(sock);    
    //pthread_cancel(socket_desc);
    pthread_exit(NULL);

    return 0;
}

void sig_handler(int signo) {
  if (signo == SIGINT) {
    printf("received SIGINT\n");

    shutdown(socket_desc, 2);
    shutdown(new_socket, 2);
    //pthread_exit(NULL);

    exit(0);
    //abort();
  }
}
