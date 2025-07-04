#include <stdio.h>

#define LOWER 0
#define UPPER 1000

/*
Bug Report:
1. Fixed the issue where the program concatenated numbers instead of adding them.
2.No use for stdlib.h.
3.Int number not in first row of function.
*/
void welcome(void);
void usage(void);
void getNumber(void);
void printTwice(int number);

int main(void)
{
    welcome();
    return 0;
}

/*
This function prints "welcome".
input: none
output: none
*/
void welcome(void)
{
    printf("Welcome to my cool program!\n");
    usage();
}

/*
This function prints what the program is for.
input: none
output: none
*/
void usage(void)
{
    printf("My program gets a number from you - and prints it twice in a row!\n");
    getNumber();
}

/*
The function gets a number.
input: none
output: none
*/
void getNumber(void)
{
    printf("Please enter a number between %d and %d: \n", LOWER, UPPER);
    int number = 0;
    scanf("%d", &number);
    while (number < LOWER || number > UPPER)
    {
        printf("Invalid choice! Please enter a number between %d and %d: \n", LOWER, UPPER);
        scanf("%d", &number);
    }
    printTwice(number);
}

/*
Prints the number twice by adding it.
input: the number we got from the user.
output: none
*/
void printTwice(int number)
{
    printf("The number added twice: %d\n", number + number);
}
