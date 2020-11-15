#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <http.h>

/*char* getBinaryFile(char *filename) {
    FILE *img = fopen(filename, "rb");
    fseek(img, 0, SEEK_END);
    unsigned long filesize = ftell(img);
    
    //printf("filesize : %lu\n", filesize);
    
    char *buffer = (char*)malloc(sizeof(char)*filesize);
    rewind(img);
    // store read data into buffer
    fread(buffer, sizeof(char), filesize, img);

    // send buffer to client
    int sent = 0;
    while (sent < filesize)
    {
        int n = send(clientsocket, buffer + sent, filesize - sent, 0);
        if (n == -1)
            break;  // ERROR

        sent += n;
    }

    return buffer;
}*/

int fileEsists(char *filename) {
    FILE *pFile;
    if((pFile = fopen(filename,"r"))!=NULL) {
        return 1;
        fclose(pFile);
    }

    return 0;
}

char* getBinaryFile(char *filename) {
    FILE * pFile;
    long lSize;
    char * buffer;
    size_t result;

    pFile = fopen (filename, "rb");
    if (pFile==NULL) {
        fputs ("File error",stderr); 
        exit (1);
    }

    // obtain file size:
    fseek (pFile, 0, SEEK_END);
    lSize = ftell (pFile);
    rewind (pFile);

    // allocate memory to contain the whole file:
    buffer = (char*) malloc(sizeof(char)*lSize);
    if (buffer == NULL) {
        fputs ("Memory error",stderr); 
        exit (2);
    }

    // copy the file into the buffer:
    result = fread(buffer,1,lSize,pFile);
    if (result != lSize) {
        fputs ("Reading error",stderr); 
        exit (3);
    }

    /* the whole file is now loaded in the memory buffer. */

    // terminate
    fclose(pFile);
    //free (buffer);
    return buffer;
}

unsigned long getFileSize(char *filename) {
    // opening the file in read mode 
    FILE* fp = fopen(filename, "r"); 
  
    // checking if the file exist or not 
    if (fp == NULL) { 
        printf("File Not Found!\n"); 
        return -1; 
    } 
  
    fseek(fp, 0L, SEEK_END); 
  
    // calculating the size of the file 
    long int res = ftell(fp); 
  
    // closing the file 
    fclose(fp); 
  
    return res; 
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
