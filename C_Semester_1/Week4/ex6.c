#include <stdio.h>
#include <conio.h>

int main()
{
	int const tday=2024;
	char first = ' ';
	char second = ' ';
	char third = ' ';
	int year = 0;
	int num = 0;
	printf("enter first letter:");
	scanf("%c",&first);
	getchar();
	printf("enter second letter:");
	scanf("%c",&second);
	getchar();
	printf("enter third letter:");
	scanf("%c",&third);
	printf("Hey %c%c%c, what year you were born?\n",first,second,third);
	scanf("%d",&year);
	printf("Please choose a number that you like between 1-100:\n");
	scanf("%d",&num);
	printf("You are %d Years old\n",tday-year);
	printf("%d %% %d = %d",(tday-year),num,(tday-year)%num);
    return 0;
}
