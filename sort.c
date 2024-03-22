#include <stdio.h>
#include <stdlib.h>
#define NMAX 4 
#define DEBUG 1 

void read_array(int *arr);
int read_length(int *length);
void print(int *arr); 
void sort(int *arr, int *count);
void swap(int *left, int *right);

int main() {
//    int arr[NMAX];
    int *length;
    int *arr;
//    int count = 0;

//    printf("%d", (read_length(length)));
    if (read_length(length)) {
        if (DEBUG == 1) printf("Array length has been successfully read. Value is: %d\n", *length);
        arr = (int*)calloc(*length, sizeof(int));
        if (arr != NULL) {
            if (DEBUG == 1) printf("Memory for array allocated: %p\n", arr);
        } else {
            if (DEBUG == 1) printf("Memory allocation ERROR!\n");
        }
    }
/*
        if (DEBUG == 1) printf("\nStarted. Array size is %d\n", NMAX);
    read_array(arr);
    print(arr);
        if (DEBUG == 1) printf("\n\n");
    sort(arr, &count);
    print(arr);
        if (DEBUG == 1) printf("Iterations: %d\n", count);
*/
    return 0;
}
int read_length(int *length) {
    int flag = 0;
        if (DEBUG == 1) printf("Enter array length:\n");
    if (scanf("%d", length) == 1) {
        flag = 1;
    }
    return flag;
}

void read_array(int *arr) {
    if (DEBUG == 1) printf("Reading array\n");
    for (int i=0; i<NMAX; i++) {
        scanf("%d", &arr[i]);
    }
}

void print(int *arr) {
    printf("Printing array\n");
    for (int i=0; i<NMAX; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void sort(int *arr, int *count) {
    if (DEBUG == 1) printf("Sorting array\n");
    for (int i=0; i<NMAX-1; i++) {
        *count += 1;;
        int *left = &arr[i];
        int *right = &arr[i+1];
        if (DEBUG == 1) printf("if (%d > %d) then swap, iteration %d\n", *left, *right, *count);
        if (*left > *right) {
            swap(left, right);
            sort(arr, count);
        }
    }
    if (DEBUG == 1) printf("\n");
}
void swap(int *left, int *right) {
    int buffer;

    if (DEBUG == 1) printf("Swapping left=%d and right=%d\n", *left, *right);
    buffer = *left;
    *left = *right;
    *right = buffer;
    if (DEBUG == 1) printf("Completed swapping left=%d and right=%d\n", *left, *right);
}
