#include <stdio.h>
#include <string.h>

int main(void) {
    int result = strcmp("test1", "test2");
    int result2 = strcmp("test", "test");

    printf("result1 : %i", result);
    printf("result2 : %i", result2);

    return 0; 
}