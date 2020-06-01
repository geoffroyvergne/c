#include <stdio.h>
#include "../lib/test-lib.h"

/*void printHelloWorld() {
    printf("printHelloWorld : Hello World !\n");
}

void printText(char *text) {
    printf("PrintText : %s\n", text);
}

char* getText() {
    return "getText : Hello World";
}*/

int main() {
    printHelloWorld();
    printText("Hello World !");
    printf("%s", getText());
}
