#include <stdio.h>
int main()
{
	char input = ' ';
	scanf("%c",&input);
	if (input == 'C')
	{
		printf("UPPER");
	}
	if (input == 'c')
	{
		printf("LOWER");
	}
	else
	{
		printf("illegal character");
	}	
    return 0;
}
