#include <stdio.h>
#include <stdlib.h>

void printBeforeX(int* arr, int n, int* x);
int main()
{
    int arr[] = {4, 8, 6, 2, 1, 3, 5, 7, 8, 9, 5};
    int SIZE = sizeof(arr) / sizeof(arr[0]);
    int offset = 0;
    printf("Please enter an offset to search in the array’s address domain: ");
    scanf("%d", &offset);
    getchar();
    printBeforeX(arr, SIZE, arr + offset);
    getchar();
    return 0;
}
/*
Function to print the array elements up to a given index   
input: int* arr - the array to print, int n - the size of the array, int* x - the index to print up to
output: void
*/
void printBeforeX(int* arr, int n, int* x)
{
    if (x < arr || x >= arr + n)
    {
        printf("Index %ld is out of the array range\n", x - arr);
        return;
    }
    printf("The array elements up to the index %ld are: ", x - arr);
    for (int* p = arr; p < x; p++) 
    {
        printf("%d ", *p);
    }
    printf("\n");
}

