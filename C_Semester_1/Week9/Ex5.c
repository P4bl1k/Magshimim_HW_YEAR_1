//DONE
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int areValidNumbers(int num1, int num2, int num3);

int main(void)
{
    int num1 = 0;
    int num2 = 0;
    int num3 = 0;
	srand(time(NULL));
    do
    {
        num1 = rand() % 101;
        num2 = rand() % 101;
        num3 = rand() % 101;

    } 
	while (!areValidNumbers(num1, num2, num3)); //Check If Nums Are Valid
    printf("The numbers are: %d, %d, %d\n", num1, num2, num3);

    return 0;
}

/*
Task: Function Check If the 3 random nums are valid
Input: 3 Random Numbers
Output: True or False
*/
int areValidNumbers(int num1, int num2, int num3)
{
    int hasEven = 0;
    int hasOdd = 0;
    int hasGreaterThan50 = 0;

    // If one is Even
    if (num1 % 2 == 0 || num2 % 2 == 0 || num3 % 2 == 0)
    {
        hasEven = 1;
    }
    // If one is Odd
    if (num1 % 2 != 0 || num2 % 2 != 0 || num3 % 2 != 0)
    {
        hasOdd = 1;
    }

    //If one is greater than 50
    if (num1 > 50 || num2 > 50 || num3 > 50)
    {
        hasGreaterThan50 = 1;
    }

    //Return Of Answer 
    return hasEven && hasOdd && hasGreaterThan50;
}

