#include <stdio.h>
// gcc -Wall -Wextra -Werror handling_array.c

int read_uder_input_digit();

int main() {
    int ar[4];  // creating array of 4 int, array is not array, but pointer to first element

    for (int *p = ar; p-ar<4; p++) {
        *p = read_uder_input_digit();
        printf("*p = %d, ar = %p, p = %p\n", *p, ar, p);
        printf("digit value of p-ar = %ld\n", p-ar);
    }    

    return 0;
}

int read_uder_input_digit() {
    int d;
    
    printf("Enter integer: ");
    if (scanf("%d", &d) != 1) {
        d = 77777777;
    }

    return d;
}
