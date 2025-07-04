/*********************************
* Class: MAGSHIMIM C2			 *
* Week 2           				 *
* HW solution   			 	 *
**********************************/
#include <stdio.h>
#include <time.h>

#define RANGE 10

void mystery(int*,int*);

int main(void)
{
	int a = 0, b = 0;
	srand(time(NULL)); // seed for rand
	a = (rand() % RANGE) + 1;
	b = (rand() % RANGE) + 1;
	
	mystery(&a, &b);
	printf("a: %d b: %d \n", a, b);	

	return 0;
}

/*
Function Checks Which number is bigger and by this desides If To add one to another to to substract each other. 
input: two pointers of int
output: none
*/
void mystery(int* x, int* y)
{
	if(*x < *y)
	{
		*x = *x + *y;
	}
	else
	{
		*y = *x - *y;
	}
}
// Yes, The value Of A/B changes because it changes the Value that is exactly in the pointer,And it Directly Changes The A/B.