#include <stdio.h>
int main() {
    int num = 0;

    do {
        printf("Enter a number: ");
        scanf("%d", &num);
        if (num < 1 || num > 1000) 
        {
            printf("Number is out of range (1-1000). Try again.\n");
        } 
        else if (num % 2 == 1) 
        {
            printf("Number is odd. Try again.\n");
        }
    }
    while (num % 2 == 1 || num < 1 || num > 1000);

    printf("You entered a valid even number: %d\n", num);
    return 0;
}