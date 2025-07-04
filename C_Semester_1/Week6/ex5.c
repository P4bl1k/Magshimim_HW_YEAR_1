#include <stdio.h>

int main() 
{	
	int i = 0;
	int j = 0;
    int cnt = 0;
    for (i = 2; i <= 1000; i++)
    {
        int check = 1;
        for (j = 2; j * j <= i; j++)
        {
            if (i % j == 0) 
            {
                check = 0;
                break;
            }
        }
        if (check == 1) 
        {
            printf("Prime Number: %d\n", i);
            cnt++;
        }
    }
    printf("Total Prime Numbers: %d\n", cnt);
    return 0;
}
