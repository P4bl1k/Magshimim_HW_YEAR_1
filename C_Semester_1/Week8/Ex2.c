#include <stdio.h>

void geometricSum(float a0, float q, int num);

int main(void)
{
    float a0 = 0;
    float q = 0;
    int num = 0;

    // Input the first element, ratio, and the number of elements
    printf("Enter first element of the series: ");
    while(scanf("%f", &a0) != 1) 
    {
        printf("Invalid input for first element.\nTry Again:");
    }

    printf("Enter the series ratio: ");
    while(scanf("%f", &q) != 1) 
    {
        printf("Invalid input for ratio.\nTry Again:");
    }

    printf("Enter number of elements: ");
    while(scanf("%d", &num) != 1 || num <= 0) 
    {
        printf("Number of elements must be a positive integer.\nTry Again:");
		
    }

    // Call the function to calculate and print the sum
    geometricSum(a0, q, num);

    return 0;
}
/*
Function to calculate the sum of the first 'num' elements in the geometric series
input: first element, ratio, and the number of elements
output: none
*/
void geometricSum(float a0, float q, int num) 
{
	int i = 0;
    float result = 0; 
    float term = a0;  // Start with the first term

    for (i = 0; i < num; i++) 
    {
        result += term; // Add the current term to the sum
        term *= q;      // Calculate the next term by multiplying with the ratio
    }

    printf("The sum of the first %d elements is %.2f\n", num, result);
}
