#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void function(int a, int b); 
void function2(int a, int b); 

int main(void)
{
	int a = 0;
    int b = 0;
	printf("Enter a number:\n");
	scanf("%d", &a);
	getchar();
	printf("Enter a smaller number:\n");
	scanf("%d", &b);
	getchar();

	printf("First function:\n");
	function(a, b);
    
	printf("Second function:\n");
	function2(a, b);
	getchar();
	return 0;
}

/*
function prints all the numbers from a to b that are divisible by b.
input: a - a positive integer
       b - a smaller positive integer
Runtime: O(a - b)
*/
void function(int a, int b)
{
	int i = 0;
	for (i = a; i >= b; i--)  // O(a - b) iterations
	{
		if (i % b == 0)
		{
			printf("%d ", i);
		}
	}
	printf("\n");
}

/*
Function prints all the numbers from a to b that are divisible by b.
input: a - a positive integer
       b - a smaller positive integer
Runtime: O(a / b)
*/
void function2(int a, int b)
{
	int i = 0;
	for (i = b; i <= a; i += b)  // O(a / b) iterations
	{
		printf("%d ", i);
	}
	printf("\n");
}
