#include <stdio.h>
#include <stdlib.h>

#define ARR_LENGTH 2

void initArray(int arr[]); //Wrong Type of function
void printGrades(int first, int second);

int main(void)
{
	int myGrades[] = {0,0};
	initArray(myGrades); //Wrong syntax of bringing Function
	int first = myGrades[0]; //Theres No Option Of Choice The Placement in Array
	int second = myGrades[1];	
	
	printGrades(first, second);
	return 0;
}

/*
Function will change values of array (input from user)
input: array to change
output: fixed array
*/
void initArray(int arr[]) //Wrong Type of function
{
	printf("Enter grades in English and history: ");
	scanf("%d %d", &arr[0], &arr[1]);
	//No Need of Return
}

/*
Function will print two grades
input: the grades to print
output: none
*/
void printGrades(int first, int second)
{
	printf("My grade in English is: %d!\n",first);
	printf("My grade in History is %d! Great Success!\n",second);
}
// Answer For 4B: This Happens Cause The Number Shows The Placement of First Data In The Array In The Whole Memory Of Hard Drive Disk In Pc, The Number That Shown Isnt The Terue Number of Placement Cause It Is Printed By %d That Can Show number only until 2147483647, after That Number It Overflows and starts all over from the first possible number of int.