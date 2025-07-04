#include <stdio.h>
#include <stdbool.h>

int main()
{
    int number = 0;
	int evens = 1;
    int odds = 1;
	int i = 0;
    printf("Enter Positive Number:");
    scanf("%d", &number);
	
    for (i = 0; i <= 9; i++) 
	{
        int temp = number;
        int digitFound = 0;
		int flag = 0;
        while (temp > 0 && flag != 1) 
		{
            int digit = temp % 10;
            if (digit == i) 
			{
                digitFound = true;
                flag = 1;
            }
            temp /= 10;
        }

        if (digitFound) 
		{
            if (i % 2 == 0)
			{ 
                evens = evens * i;
            } 
			else 
			{ 
                odds = odds * i;
            }
        }
    }
	printf("The Sum of Evens Is:%d\n",evens);
	printf("The Sum of Odds Is:%d",odds);

    return 0;
}
