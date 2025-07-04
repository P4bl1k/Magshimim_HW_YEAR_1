#include <stdio.h>

int main() {
    char input = 'y';
    int num = 1;

    while (input == 'y')
    {
        printf("Enter a number: ");
        scanf("%d", &num);

        if (num < 0) {
            printf("Invalid input! Number must be non-negative.\n");
            continue; 
        }

        int cnt = 1; 
        while (cnt <= num) {
            printf("%d ", (cnt * cnt));
            cnt++;
        }
        printf("\n");

        printf("Would you like to try again? (Press 'y' for yes or any other key for no): ");
        getchar(); 
        input = getchar();
    }

    return 0;
}
