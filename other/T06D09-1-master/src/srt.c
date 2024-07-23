#include <stdio.h>

int main() {
    int arr[5] = {9, -6, 11, 4, 0};
/*
    for (int i = 0; i < 4; i++) {
        while (arr[i]>arr[i+1]) {
            int temp = arr[i];
            arr[i] = arr[i+1];
            arr[i+1] = temp;
        }
    }    
*/  
    for (int *p = arr; p-arr < 5; p++) { printf("%d ", *p); }
    printf("\n");    
    for (int i = 0; i < 5; i++) { printf("%d ", arr[i]); }
    printf("\n");    
    return 0;
}
