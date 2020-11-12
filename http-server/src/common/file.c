#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <http.h>

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

char* indexPath(char* uri, char* target) {
    
    if(strcmp(uri, "/") == 0) {
        //char* INDEX_HTML_LIST[] = {"index.htm", "index.html"};

        size_t i = 0;
        for( i = 0; i < sizeof(INDEX_HTML_LIST) / sizeof(INDEX_HTML_LIST[0]); i++) {
            char *content = (char *) malloc( sizeof(char) * 2000 );
            char *indexUri = (char *) malloc( sizeof(char) * 2000 );
            
            strcpy(indexUri, target);
            strcat(indexUri, uri);
            strcat(indexUri, INDEX_HTML_LIST[i]);
            
            content = read_file(indexUri);

            if(content != NULL) {
                strcpy(indexUri, uri);
                strcat(indexUri, INDEX_HTML_LIST[i]);

                puts(indexUri);
                return indexUri;
            } 

            free(content);
            free(indexUri);
        }
    } 
    return uri;
}
