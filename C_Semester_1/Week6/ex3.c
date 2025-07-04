#include <stdio.h>

int main(void)
{
	int myLoopyVar = 1; 
	int multiplyBy = 0;
	
	printf("Daniel Presents: The Board of Multiplication!\n");
	
	for(myLoopyVar = 1; myLoopyVar < 11; myLoopyVar++)
	{	
		for(multiplyBy = 1; multiplyBy < 11; multiplyBy++)
			printf("%d ", myLoopyVar * multiplyBy);
		printf("\n");
	}
	return 0;
}
