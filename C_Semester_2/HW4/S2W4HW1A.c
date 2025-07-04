/*********************************
* Class: MAGSHIMIM C2			 *
* Week 4           				 *
* HW solution   			 	 *
**********************************/

#include <stdio.h>
#include <stdlib.h>
int main()
{
    int size = 5;
    int* arr = NULL;
    arr = (int*)malloc(size * sizeof(int));
    if(!arr)
    {
        printf(":(");
        return 1;
    }
    else
    {
        printf("Memory Allocated\n");
        free(arr);
        printf("And Freed Successfully");
    }
    return 0;
}
