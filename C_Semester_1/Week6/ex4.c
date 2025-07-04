#include <stdio.h>

int main() {
    int num = 0;
    int i = 0;
    int j = 0;
    int k = 0;
    printf("Enter number (1-9): ");
    scanf("%d", &num);
    while(k != 1)
    {
        if (num < 1 || num > 9) 
        { 
            printf("Invalid input! Please enter a number between 1 and 9.\n");
            scanf("%d", &num);
        }
        else
        {
            k++;
        }
    }
    for (i = 1; i <= num; i++) {
        for (j = 1; j <= i; j++) {
            printf("%d ", i);
        }
        printf("\n");
    }

    return 0;
}