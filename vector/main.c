#include <stdio.h>
#include <stdlib.h>
#include "vec.h"

int main(int argc, char **argv) {

    printf("C Vector\n");

    int* num_vec = vector_create();
    vector_add(&num_vec, 5);

    printf("first item: %d\n", num_vec[0]);

    int num_ages = vector_size(num_vec);

    return EXIT_SUCCESS;
}
