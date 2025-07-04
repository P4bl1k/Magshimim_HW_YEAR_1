#include <stdio.h>

#define WINNING_NUMBER 100

int main()
{
    int last = 0;
	int current = 0;
	int player = 1;
	int flag = 1;

    printf("Numbers Game!\n");
    while (flag != 0)
	{
        printf("Player %d: ", player);
        scanf("%d", &current);

        if ((last == 0 && current >= 1 && current <= 10) || (current > last && current <= last + 10))
		{
            last = current;
            if (current >= WINNING_NUMBER)
			{
                printf("Player %d Won!\n", player);
                flag = 0;
            }
            player = 3 - player; 
        } 
		else 
		{
            printf("Try Again.\n");
        }
    }

    return 0;
}
