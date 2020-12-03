#include <errno.h>
#include <stdlib.h>

int main(void){
    int result = ENOMEM;
    char * buffer = malloc(2);

    if (buffer != NULL){
        result = 0;
        buffer[0] = 'a';
        buffer[1] = 'b';
        free(buffer);
        buffer[0] = 'a';
    }

    return result;
}
