/*********************************
* Class: MAGSHIMIM C2			 *
* Week 2           				 *
* HW solution 			 		 *
**********************************/

#include <stdio.h>

void add(int* x, int* y, int* sum);

int main(void)
{
	int a = 0, b = 0, sum = 0;
	int* c = &b; //Was No & Before B
	printf("Enter two numbers: ");
	scanf("%d %d", &a, &b);
	//No need of getchar 
	add(&a, c, &sum); //Casted A Pointer(&) For A Pointer XD
	printf("The sum of a and b is: %d", sum);
	// Also No Need For GetChar
	return 0;
}

void add(int* x, int* y, int* sum) 
{ 
	*sum = *x + *y; //Sum And x Wasnt In Pointers
}
// My Tip For Daniel: Make the More Accurate Usage Of Pointers and Stop Using Getchars, 
//Sometimes Your Getchars are Useless in Your Code.