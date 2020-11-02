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

    // Prepare sockaddr_in structure
    //server.sin_addr.s_addr = inet_addr(host);

    // used to expose on all address
    server.sin_addr.s_addr = INADDR_ANY;

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
    //setbuf(stdout, NULL);  
    printf("%s %s %s %s %d %s %s\n", 
        http_header->http->verb, 
        http_header->header->host,
        http_header->http->path, 
        http_header->http->protocol, 
        http_header->http->status_code,
        http_header->header->accept,
        http_header->header->user_agent
    );

    //printf("strlen : %lu \n", strlen(http_header->header->host));

    //puts(http_header->http->protocol);

    /*char *log = (char *) malloc( sizeof(char) * 2000 );
    
    strncat(log, http_header->http->verb, strlen(http_header->http->verb));
    strcat(log, " ");
    strncat(log, http_header->header->host, strlen(http_header->header->host));
    strcat(log, " ");
    strncat(log, http_header->http->path, strlen(http_header->http->path));
    strcat(log, " ");
    strncat(log, http_header->http->protocol, strlen(http_header->http->protocol));
    strcat(log, " ");
    strncat(log, http_header->http->status_code, strlen(http_header->http->status_code));
    strcat(log, " "); 
    strncat(log, http_header->header->user_agent, strlen(http_header->header->user_agent));
    strcat(log, " ");  
    strncat(log, http_header->header->accept, strlen(http_header->header->accept));
    strcat(log, " ");       

    puts(log);    */
}

void *connection_handler(void* params) {
    struct connection_handler_params *connection_params = (struct connection_handler_params*)params;

    int sock = *(int*) connection_params->socket_desc;   
    char *client_message = (char *) malloc( sizeof(char) * 2000 );
    char *uri = (char *) malloc( sizeof(char) * 2000 );

    recv(sock, client_message, 2000, 0);

    struct http_header* http_header = extract_headers(client_message, "\n");    

    strcpy(uri, connection_params->target);
    strcat(uri, http_header->http->path);

    char* contentType = getContentType(uri);
    http_header->http->content_type = contentType;
    
    char *content = read_file(uri);

    char *message = (char *) malloc( sizeof(char) * 2000 );
    char* content_len = (char *) malloc( sizeof(char) * 5 );

    if(content != NULL) {
        http_header->http->status_code = 200;
        http_header->http->status_reason = "OK";  
        message = create_message(content, http_header);
        write(sock, message, strlen(message));         
    } else {
        char* not_found_uri = (char *) malloc( sizeof(char) * 2000 );
        strcpy(not_found_uri, connection_params->target);
        strcat(not_found_uri, "/error/404.html");
        char *content = read_file(not_found_uri);

        http_header->http->status_code = 404;
        http_header->http->status_reason = "NOT FOUND";
        message = create_message(content, http_header);
        write(sock, message, strlen(message));        

        free(not_found_uri);
    }

    tcp_log(http_header);
    free(http_header);
    free(content);
    free(message);
    free(content_len);
    free(uri);
    close(sock);    
    pthread_exit(NULL);

    return 0;
}

char* create_message(char *content, struct http_header* http_header) {
    char *result = (char *) malloc( sizeof(char) * 2000 );
    //char* content_len = (char *) malloc( sizeof(char) * 5 );
    //sprintf(content_len, "%lu", strlen(content));

    /*strcat(result, "HTTP/1.1");
    strncat(result, " ", 1);
    strncat(result, http_code, strlen(http_code));
    strncat(result, " ", 1);
    strncat(result, http_reason, strlen(http_reason));
    strcat(result, "\r\nContent-Length:");
    strncat(result, content_len, strlen(content_len));
    strcat(result, "\r\n\r\n");
    strncat(result, content, strlen(content));*/

    char* template = "%s %d %s\r\nContent-Length: %lu\r\nContent-Type: %s\r\n\r\n%s\n";
    //char* template = "%s %d %s\r\nContent-Type: %s\r\n\r\n%s\n";

    //printf("%s", result);
    sprintf(result, template, 
        toUpperCase(http_header->http->protocol),
        http_header->http->status_code, 
        http_header->http->status_reason, 
        strlen(content),
        http_header->http->content_type, 
        content
    );

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
