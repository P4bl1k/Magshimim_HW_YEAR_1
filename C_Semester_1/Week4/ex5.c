#include <stdio.h>
#include <conio.h>

int main()
{
	char first = ' ';
	char second = ' ';
	char third = ' ';
	printf("enter first letter:");
	scanf("%c",&first);
	getchar();
	printf("enter second letter:");
	scanf("%c",&second);
	getchar();
	printf("enter third letter:");
	scanf("%c",&third);
	printf("The name is : %c%c%c",first,second,third);
    return 0;
}
