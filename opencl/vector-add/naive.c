#include <stdio.h>
#include <stdlib.h>

int main() {
    printf("OpenCl\n");

    const int LIST_SIZE = 1024;

    int *A = (int*)malloc(sizeof(int)*LIST_SIZE);
    int *B = (int*)malloc(sizeof(int)*LIST_SIZE);
    int *C = (int*)malloc(sizeof(int)*LIST_SIZE);

    for(int i = 0; i < LIST_SIZE; i++) {
        C[i] = A[i] + B[i];
    }
}
