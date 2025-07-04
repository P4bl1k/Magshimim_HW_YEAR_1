#include <stdio.h>

int main() {
    int number = 0;
    int sum = 0;
	int i = 1;
    printf("Enter a number: ");
    scanf("%d", &number);
    for (i = 1; i <= number / 2; i++) 
	{
        if (number % i == 0) 
		{
            sum += i;
        }
	}
    if (number == sum)
	{
        printf("%d is a perfect number.\n", number);
    } 
	else 
	{
        printf("%d is not a perfect number.\n", number);
    }

    return 0;
}
