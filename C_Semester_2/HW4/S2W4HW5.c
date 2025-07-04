/*********************************
* Class: MAGSHIMIM C2			 *
* Week 4           				 *
* HW solution   			 	 *
**********************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int* createArr(int len);

int main(void)
{
	int size = 0;
	int* pArr = 0;

	printf("Enter a number of cells: ");
    //Enterting to the Size Itself,not the value of it.
	scanf("%d", &size);
    pArr = createArr(size);
    printf("The array is at address %p: ", pArr);
    free(pArr);
    getchar();
	getchar();
	return 0;
}

/*
Function creates an array
input: number of cells in the array
output: pointer to the new array
*/
int* createArr(int size)
{
    //forgot to multiply by the size of int
	int* pArr = (int*)malloc(size*sizeof(int));
	int i = 0;
	for(i = 0; i < size; i++)
	{
		printf("Please enter a number for index %d: ",i);
        //Entering to the Pointer Itself, Not the Size of it
		scanf("%d",&pArr[i]);
	}
    //Remove this useless line that crashes the program
	return pArr;
}
//Yes, Ronny found it in the function bcs we couldnt enter the numbers inside of the indexes of the array.