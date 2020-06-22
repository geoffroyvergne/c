#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Just for information : 
char * mystrcat( char * destination, const char * source ) {
    char * returnValue = destination;
    while( *destination ) ++destination;
    while( *destination++ = *source++ );
    return returnValue;
}
*/

int main() {

    char *client_message = "test";
    char *prefix = "Client message : ";
    char *message = (char *) malloc( 50 );

    strcpy(message, prefix);
    strcat(message, " ");
    strcat(message, client_message);
    strcat(message, "\n");

    printf("Message : %s", message);

    //free(client_message);
    //free(prefix);
    //free(message);

    return 0;
}