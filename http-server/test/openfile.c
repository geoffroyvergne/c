#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void writeBinaryFile(char* buffer, char *filename, unsigned long size) {

    printf("size : %lu", size);

    FILE * pFile;
    pFile = fopen(filename, "wb");
    fwrite(buffer , size, 1, pFile);
    fclose(pFile);
}

unsigned long fileSize(char *filename) {
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

int main() {
    char* buffer = getBinaryFile("W3C.jpg");

    printf("strlen(buffer) = %lu\n", strlen(buffer));
    printf("buffer = %s\n", buffer);

    writeBinaryFile(buffer, "W3C-copy.jpg", fileSize("W3C.jpg"));
}
