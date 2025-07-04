/*********************************
* Class: MAGSHIMIM C2			 *
* Week 4           				 *
* HW solution   			 	 *
**********************************/

#include <stdio.h>
#include <stdlib.h>

void printArray(int* arr, int size);
void swap(int *xp, int *yp);
void sortarray(int* arr, int size);

int main()
{
    int size = 0;
    int* arr = 0;
    int i = 0;

    printf("Enter A Size: ");
    scanf("%d", &size);

    arr = (int*)malloc(size * sizeof(int));
    if (!arr)
    {
        printf(":(");
        return 1;
    }
    else
    {
        printf("Memory Allocated\n");
        for (i = 0; i < size; i++)
        {
            printf("Number %d: ", (i+1));
            scanf("%d",&arr[i]);
        }

        sortarray(arr, size);
        printArray(arr, size);

        free(arr);
        printf("And Freed Successfully\n");
    }
    getchar();
    getchar();
    return 0;
}

void printArray(int* arr, int size)
{
    int i = 0;
    for (i = 0; i < size; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}

void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sortarray(int* arr, int size)
{
    int i = 0;
    int j = 0;
    for (i = 0; i < size - 1; i++)
    {
        for (j = 0; j < size - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}
