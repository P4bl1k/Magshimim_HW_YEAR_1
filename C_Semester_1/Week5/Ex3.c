#include <stdio.h>
int main()
{
	int num1 = 0;
	int num2 = 0;
	int selected = 0;
	printf("Enter First Number:");
	scanf("%d",&num1);
	printf("Enter Second Number:");
	scanf("%d",&num2);
	printf("Enter An Action:");
	getchar();
	scanf("%d",&selected);
	switch (selected) 
	{
		case 1:
			printf("%d + %d = %d",num1,num2,(num1+num2));
			break;
		case 2:
			printf("%d - %d = %d",num1,num2,(num1-num2));
			break;
		case 4:
			if (num2 == 0)
			{
				printf("can't divide by zero!!!");
			}
			else
			{
				printf("%d / %d = %f",num1,num2,1.0*(num1/num2));
			}
			break;
		case 3:
			printf("%d * %d = %d",num1,num2,(num1*num2));
			break;
		default:
			printf("choice is not valid");
			break;
}
    return 0;
}
