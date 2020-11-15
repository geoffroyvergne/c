#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <signal.h>
#include <netinet/in.h>
#include <tcp-server.h>
#include <file.h>
#include <string-utils.h>
#include <http.h>

void sig_handler(int signo);

struct connection_handler_params {
    void *socket_desc;
    char *target;
};

int socket_desc, new_socket, sockaddr_in_size, *new_sock;
struct sockaddr_in server, client;

int tcp_connect(int port, char* host, char* target) {  

    if (signal(SIGINT, sig_handler) == SIG_ERR) {
        printf("\ncan't catch SIGINT\n");
    } 

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_desc == -1) {
        puts("Could not create socket");
    }

    if(strstr(host, "0.0.0.0")) {
        server.sin_addr.s_addr = INADDR_ANY;
    } 
    
    if(strstr(host, "127.0.0.1")) {
        server.sin_addr.s_addr = INADDR_LOOPBACK;
    } 
    
    if (strstr(host, "localhost")) {
        server.sin_addr.s_addr = INADDR_LOOPBACK;
    } 
    
    server.sin_addr.s_addr = inet_addr(host);

    // Prepare sockaddr_in structure
    //server.sin_addr.s_addr = inet_addr(host);

    // used to expose on all address
    //server.sin_addr.s_addr = INADDR_ANY;

    // used to expose on localhost
    //server.sin_addr.s_addr = INADDR_LOOPBACK
    
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (setsockopt(socket_desc, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0) {
        perror("setsockopt(SO_REUSEADDR) failed");
    }
   
    if (bind(socket_desc, (struct sockaddr *) &server, sizeof(server)) ==- 1) {
        perror("bind failed");
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

void tcp_log(struct http_header* http_header) {
    printf("%s %s %s %s %d %s %s\n", 
        http_header->http->verb, 
        http_header->header->host,
        http_header->http->path, 
        http_header->http->protocol, 
        http_header->http->status_code,
        http_header->header->accept,
        http_header->header->user_agent
    );
}

void *connection_handler(void* params) {
    struct connection_handler_params *connection_params = (struct connection_handler_params*)params;

    int sock = *(int*) connection_params->socket_desc;   
    char *client_message = (char *) malloc( sizeof(char) * 2000 );
    char *uri = (char *) malloc( sizeof(char) * 2000 );

    recv(sock, client_message, 2000, 0);

    struct http_header* http_header = extract_headers(client_message, "\n");    

    // check if it is better with index.html
    http_header->http->path= indexPath(http_header->http->path, connection_params->target);

    strcpy(uri, connection_params->target);
    strcat(uri, http_header->http->path);

    //char* contentType = getContentType(uri);
    http_header->http->content_type = getContentType(uri);

    int binary = isBinary(uri);

    char *message = (char *) malloc( sizeof(char) * 2000 );
    char* content_len = (char *) malloc( sizeof(char) * 5 );

    if(fileEsists(uri)) {
        if(binary) {
            char *buffer = getBinaryFile(uri);

            http_header->http->status_code = 200;
            http_header->http->status_reason = "OK";  

            unsigned long filesize = getFileSize(uri);

            message = create_message("", filesize, http_header);
        
            send(sock, message, strlen(message), 0); 
            send(sock, buffer, filesize, 0);
        } else {
            char *content = read_file(uri);
            http_header->http->status_code = 200;
            http_header->http->status_reason = "OK";  
            message = create_message(content, strlen(content), http_header);
            write(sock, message, strlen(message));   

            free(content);      
        }
    } else {
        char* not_found_uri = (char *) malloc( sizeof(char) * 2000 );
        strcpy(not_found_uri, connection_params->target);
        strcat(not_found_uri, "/error/404.html");
        char *content = read_file(not_found_uri);

        http_header->http->status_code = 404;
        http_header->http->status_reason = "NOT FOUND";
        message = create_message(content, strlen(content), http_header);
        write(sock, message, strlen(message));        

        free(not_found_uri);
    }

    free(message);
    free(content_len);

    tcp_log(http_header);
    free(http_header);
    
    free(uri);
    close(sock);    
    pthread_exit(NULL);

    return 0;
}

char* create_message(char *content, unsigned long contentLength, struct http_header* http_header) {
    char *result = (char *) malloc( sizeof(char) * 2000 );
    
    //accept-ranges: bytes\r\n
    char* template;

    if(strlen(content) > 0) {
        template = "%s %d %s\r\nContent-Length: %lu\r\nContent-Type: %s\r\n\r\n%s\r\n";
    } else {
        template = "%s %d %s\r\nContent-Length: %lu\r\nContent-Type: %s\r\n\r\n";
    }
    

    //printf("%s", result);
    sprintf(result, template, 
        toUpperCase(http_header->http->protocol),
        http_header->http->status_code, 
        http_header->http->status_reason, 
        //strlen(content),
        contentLength,
        http_header->http->content_type, 
        content
    );

    /*if(strlen(content > 0)) {
        strcat(result, content);
    }*/

    //puts(result);

    return result;
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
