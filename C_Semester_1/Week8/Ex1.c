#include <stdio.h>

void printNum(int num);

int main(void)
{
    int firstNum = -1;
    int secondNum = 46;

    printNum(firstNum);
    printNum(secondNum); // Removed `int` keyword here as it is incorrect syntax.
    printNum(firstNum + secondNum);
    printNum(6);

    return 0; // Added to return 0; for knowing the successful running of `main`.
}
/*
Function to print a number.
input: number from main
*/
void printNum(int num)
{
    printf("%d\n", num); // Replaced the invalid quotes with standard double quotes.
}
