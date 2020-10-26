#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>

#include <tcp-server.h>
#include <file.h>
#include <string-utils.h>
#include <http.h>

struct connection_handler_params {
    void *socket_desc;
    char *target;
};

int socket_desc, new_socket, sockaddr_in_size, *new_sock;
struct sockaddr_in server, client;

int tcp_connect(int port, char* target, char* host) {
    printf("Start http-server port : %i\n", port);

        // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_desc == -1) {
        printf("Could not create socket\n");
    }

    // Prepare sockaddr_in structure
    server.sin_addr.s_addr = inet_addr(host);
    //server.sin_addr.s_addr = INADDR_ANY;
    
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

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
        new_sock = malloc( sizeof(int) );
        *new_sock = new_socket;

        struct connection_handler_params *params;
        params = malloc(sizeof(struct connection_handler_params));

        params->socket_desc = new_sock;
        params->target = target;

        if(pthread_create(&sniffer_thread, NULL, connection_handler, (void*) params) == -1) {
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
}

int tcp_shutdown() {
    shutdown(socket_desc, 2);
    shutdown(new_socket, 2);
    pthread_exit(NULL);
}

/*char* parseHeader(char* client_message) {

    //setbuf(stdout, NULL);  
   
    char *client_message_array = strtok(client_message, " ");    

    int i=0;
    while(client_message_array != NULL) {
        if(i == 1) break;
        client_message_array = strtok(NULL, " ");
        i++;
    }

    //printf("client_message_array : %s \n", client_message_array);
    //printf("test");

    return client_message_array;
}*/

void tcp_log(struct http_header* http_header) {
    //printf("%s %s %s %s\n", http_header->http.verb, http_header->http.path, http_header->http.protocol, http_header->header.accept);

    char *log = (char *) malloc( sizeof(char) * 2000 );
    strcat(log, http_header->http.verb);
    strcat(log, " ");
    strcat(log, http_header->http.path);
    strcat(log, " ");
    strcat(log, http_header->http.protocol);

    puts(log);
    free(log);
}

void *connection_handler(void* params) {
    //setbuf(stdout, NULL);  
    struct connection_handler_params *connection_params = (struct connection_handler_params*)params;

    int sock = *(int*) connection_params->socket_desc;   
    char *client_message = (char *) malloc( sizeof(char) * 2000 );
    char *uri = (char *) malloc( sizeof(char) * 2000 );

    recv(sock, client_message, 2000, 0);

    //char *client_message_array = parseHeader(client_message);
    struct http_header http_header = extract_headers(client_message, "\n");    

    strcpy(uri, connection_params->target);
    strcat(uri, http_header.http.path);
    
    //puts(http_header.http.verb);

    char *content = read_file(uri);

    //printf("uri : %s \n", uri);
    // todo log headers
    //printf("%s %s %s accept %s\n", http_header.http.verb, http_header.http.path, http_header.http.protocol, http_header.header.accept);
    //printf("%s\n", http_header.http.verb);

    tcp_log(&http_header);

    write_message(content, &sock);
    free(uri);

    close(sock);    
    pthread_exit(NULL);

    return 0;
}

void write_message(char *content, int *sock) {
    char *message = (char *) malloc( sizeof(char) * 2000 );
    char* content_len = (char *) malloc( sizeof(char) * 5 );
        
    //char *content = "<html></html>";
    //strcpy(message, "HTTP/1.1 200 OK\r\nContent-Length: 55\r\n\r\n<!DOCTYPE html><html><body><h1>index2</h1></body></html>");

    if(content != NULL) {        
        message = create_message(content, "200", "OK");
        write(*sock, message, strlen(message));        
    } else {        
        message = create_message("<h1>404 NOT FOUND</h1>", "404", "NOT FOUND");

        /*char *uri = (char *) malloc( sizeof(char) * 2000 );
        strcpy(uri, connection_params->target);
        strcat(uri, "/error/404.html");
        char *content = read_file(uri);*/

        write(*sock, message, strlen(message));
    }

    free(content);
    free(message);

    //strcat(content, "");
    //strcat(message, "");

    free(content_len);
}

char* create_message(char *content, char* http_code, char *http_reason) {
    char *result = (char *) malloc( sizeof(char) * 2000 );
    char* content_len = (char *) malloc( sizeof(char) * 5 );
    sprintf(content_len, "%lu", strlen(content));

    strcat(result, "HTTP/1.1");
    strcat(result, " ");
    strcat(result, http_code);
    strcat(result, " ");
    strcat(result, http_reason);
    strcat(result, "\r\nContent-Length:");
    strcat(result, content_len);
    strcat(result, "\r\n\r\n");
    strcat(result, content);

    //printf("%s", result);

    return result;
}
