#include <stdio.h>
#include <stdlib.h>

void printArray(int *array, int *size);
void swap(int* xp, int* yp);
void copyArray(int *source, int *target, int *size);

void selectionSort(int array[], int *size);
void bubbleSort(int array[], int *size);
void bubbleSortPointer(int *array, int *size);
void bubbleSortRecursive(int array[], int *size);
void generateBaseArray(int *array, int size);

int main(void) {

    //int baseArray[] = { 0, 23, 14, 12, 9 };
    //int unsortedArray[5];

    int size = 20;
    int *baseArray = calloc(size, sizeof(int));
    generateBaseArray(baseArray, 20);

    printf("Base Array: \n");
    printArray(baseArray, &size);

    // Selection sort
    printf("Selection sort: \n");
    copyArray(baseArray, baseArray, &size);
    selectionSort(baseArray, &size);
    printArray(baseArray, &size);

    // Bubble sort
    printf("Bubble sort: \n");
    copyArray(baseArray, baseArray, &size);
    //bubbleSort(baseArray, &size);
    //bubbleSortPointer(baseArray, &size);
    bubbleSortRecursive(baseArray, &size);
    printArray(baseArray, &size);

    return EXIT_SUCCESS;
}

void generateBaseArray(int *array, int size) {
    //int *newArray = calloc(size, sizeof(int));
    for(int i=0; i<size; i++) {  
        *array = rand() % size;
        array++;
        //*(newArray+i) = i;
    }

    //free(*array);
    //*array = newArray;
}

void copyArray(int *source, int *target, int *size) {
    for(int i=0; i<*size; i++) {        
        *target = *source;
        source ++;
        target ++;
    }
}

void printArray(int *array, int *size) {
    for(int i=0; i<*size; i++) {
        printf("%d ", *array);
        array++;
    }
    printf("\n");
}

void swap(int* xp, int* yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void selectionSort(int array[], int *size) {
    int i, j, minIdx;

    // One by one move boundary of unsort subarray
    for(i=0; i<*size-1; i++) {
        // find the minimum element in unsorted array
        minIdx = i;
        for(j=i+1; j<*size; j++) {
            if(array[j] < array[minIdx]) {
                minIdx = j;
            }
        }

        // swap the minimum found with the first element
        swap(&array[minIdx], &array[i]);
    }
}

void bubbleSort(int array[], int *size) {
    int i, j;
    for(i=0; i<*size-1; i++) {
        // Last i elements are already in place
        for(j=0; j<*size-i-1; j++) {
            if(array[j] > array[j+1]) {
                swap(&array[j], &array[j+1]);
            }
        }
    }
}

void bubbleSortPointer(int *array, int *size) {
    int i, j, temp;

    for(i=1; i<*size; i++) {
        for(j=i+1; j<*size; j++) {
            if(*(array+j) < *(array+i)) {
                temp = *(array+i);
                *(array+i) = *(array+j);
                *(array+j) = temp;
            }
        }
    }
}

void bubbleSortRecursive(int array[], int *size) {
    if(*size == 1) {
        return;
    }

    for(int i=0; i<*size-1; i++) {
        if(array[i] > array[i+1]) {
            swap(&array[i], &array[i+1]);
        }
    }

    bubbleSortRecursive(array, size-1);
}
