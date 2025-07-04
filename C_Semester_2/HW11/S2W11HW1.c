#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>

void allSquares(int n);

int main(void)
{
	int n = 0;
	printf("Enter a number: ");
	scanf("%d", &n);
	getchar();
	printf("All squares less than %d:\n", n);
	allSquares(n);
	getchar();
    return 0;
}
/*
function allSqrs(n) prints all the squares of ints less than n.
input: n - a positive ints
output: prints all squares of ints less than n
*/
void allSquares(int n)
{
	int i = 0;
	int squareN = sqrt(n);
	for (i = 1; i <= squareN; i++)
	{
		printf("%d ", i*i);
	}
}

/*
The running time of this function is: O(sqrt(n)) operations
*/