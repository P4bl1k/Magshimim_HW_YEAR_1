#include <stdio.h>
int main()
{
	int slices = 0;
	int price = 0;
	printf("Enter The Price:");
	scanf("%d",&price);
	printf("Enter The Amount Of slices:");
	scanf("%d",&slices);
	if(slices >= 3 && price < 50)
	{
		printf("You Should Buy this pizza\n");
	}
	else if(slices > 8 && price > 50)
	{
		printf("You Should Buy this pizza\n");
	}
	else 
	{
		printf("This pizza is too expensive\n");
	}
    return 0;
}
