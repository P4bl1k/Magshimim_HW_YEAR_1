#include <stdio.h>
int main()
{
	float something = 34.39;
	something = something*2;
	printf("New State Number 1:%.2f",something);
	something = something*2;
	printf("New State Number 2:%.2f",something);
	return 0;
}
