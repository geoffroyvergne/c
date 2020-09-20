#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <string.h>

void *connection_handler(void *);
//char* read_file(char const* path);

int main(int argc, char **argv) {

    int socket_desc, new_socket, sockaddr_in_size, *new_sock;
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

    if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) {
        puts("setsockopt(SO_REUSEADDR) failed");
    }
   
    if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) ==- 1) {
        puts("bind failed\n");
        return 1;
    }

    // Listen socket
    listen(socket_desc , 3);

    // Accept incomming connections
    puts("Waiting for incoming connections...");
    sockaddr_in_size = sizeof(struct sockaddr_in);
    while ((new_socket = accept(socket_desc, (struct sockaddr *) &client, (socklen_t *) &sockaddr_in_size))) {
        
        pthread_t sniffer_thread;
        new_sock = malloc(1);
        *new_sock = new_socket;

        if(pthread_create(&sniffer_thread, NULL, connection_handler, (void*) new_sock) == -1) {
            perror("couldn't create thread\n");
            return 1;
        }
    }
    
    if( (new_socket < 0) ) {
        perror("accept failed\n");
    } 

    shutdown(socket_desc, 2);
    shutdown(new_socket, 2);
    pthread_exit(NULL);
    return 0;
}

char* getHelp() {
    return "Avaliable commands : ping quit help \n";
}

char* read_file(char *filename) {
   char *buffer = NULL;
   int string_size, read_size;
   FILE *handler = fopen(filename, "r");

   if (handler) {
       fseek(handler, 0, SEEK_END);
       string_size = ftell(handler);
       rewind(handler);

       buffer = (char*) malloc(sizeof(char) * (string_size + 1) );
       read_size = fread(buffer, sizeof(char), string_size, handler);

       
       buffer[string_size] = '\0';

       if (string_size != read_size) {           
           free(buffer);
           buffer = NULL;
       }

       fclose(handler);
    }

    return buffer;
}

void *connection_handler(void *socket_desc) {

    // GET / HTTP/1.0 <CRLF><CRLF>
    /*
    GET / HTTP/1.1
    Host: localhost:8888
    User-Agent: curl/7.70.0
    Accept: *
    */


    int sock = *(int*) socket_desc;   
    char *client_message = (char *) malloc( 2000 );
    char *message = (char *) malloc( 2000 );
    char *uri = (char *) malloc( 2000 );

    recv(sock, client_message, 2000, 0);

    char *client_message_array = strtok(client_message, " ");
    
    int i=0;
    while(client_message_array != NULL) {
        if(i == 1) break;
        client_message_array = strtok(NULL, " ");
        i++;
    }
    //puts(client_message_array);
    //printf("test");

    strcpy(uri, "www");
    strcat(uri, client_message_array);
    
    //puts(uri);

    char *content = read_file(uri);
    //char *content = "<html></html>";
    char* content_len = (char *) malloc( 5 );
    sprintf(content_len, "%lu", strlen(content));

    //strcpy(message, "HTTP/1.1 200 OK\r\nContent-Length: 55\r\n\r\n<!DOCTYPE html><html><body><h1>index2</h1></body></html>");
    strcpy(message, "HTTP/1.1 200 OK\r\nContent-Length:");
    strcat(message, content_len);
    strcat(message, "\r\n\r\n");
    strcat(message, content);
    write(sock, message, strlen(message));
    
    free(content);
    free(content_len);
    free(uri);

    close(sock);    
    pthread_exit(NULL);

    return 0;
}
