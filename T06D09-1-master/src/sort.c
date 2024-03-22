#include <stdio.h>
#define NMAX 5

int read(int *arr); // returns 0 if OK, returns 1 in case of problem
void sort(int *arr);
void print(int *arr);

int main() {
    int arr[NMAX];

    if (read(arr) != 0) {
        printf("n/a");
        return 1;
    }
    
    sort(arr);
    print(arr);

    return 0;
}

int read(int *arr) {
    char ch;
    int num;

//    for (int *p=arr; p-arr < NMAX; p++) {
    for (int i = 0; i < NMAX; i++) {
//        printf("iteration %ld\n", p-arr);
//        if (scanf("%d", p) == 1 || (ch == '\n')) {
        if (scanf("%d", &num) == 1 || (ch == '\n')) {
            arr[i] = num;
//            printf("ok\n");
            // array element saved?
        } else {
            return 1;
        }
    }

    return 0;
}

void print(int *arr) {
    for (int i=0; i<NMAX; i++) {
        printf("%d ", arr[i]);
    }
}
void sort(int *arr) {
    for (int i=0; i<NMAX; i++) {
        while (arr[i] < arr[i-1] && i-1>0 ) {
            int temp;
            temp=arr[i];
            arr[i]=arr[i-1];
            arr[i-1]=temp;
        }
    }
}
