#include <stdio.h>

int main() {
    int num = 0;
    int reversed = 0;
    int cnt = 0;

    while (cnt != 1) {
        printf("Enter a positive integer: ");
        scanf("%d", &num);

        if (num < 0) {
            printf("The input is negative. Please enter a positive integer.\n");
            continue;
        }

        int temp = num;
        reversed = 0;  

        while (temp != 0) {
            reversed = reversed * 10 + (temp % 10);
            temp /= 10;
        }

        printf("Original number: %d\n", num);
        printf("Reversed number: %d\n", reversed);

        cnt++; 
    }

    return 0;
}
