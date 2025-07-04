#include <stdio.h>
#include <stdlib.h>
void arrayInput(int *arr, int size);
void arrayEvenElements(int *arr, int size);
int main() 
{
    int arr[8] = {0};
    arrayInput(arr, 8);
    arrayEvenElements(arr, 8);
    getchar();
    return 0;
}
/*
Function to input an array
input: int *arr - the array to input, int size - the size of the array
output: void
*/
void arrayInput(int *arr, int size) 
{
    printf("Enter %d numbers: ", size);
    for (int i = 0; i < size; i++) 
    {
        scanf("%d", (arr + i));
    }
    getchar();
}
/*
Function to print the even elements of an array
input: int *arr - the array to print, int size - the size of the array
output: void
*/
void arrayEvenElements(int *arr, int size) 
{
    printf("The numbers in even indexes are: ");
    for (int i = 0; i < size; i += 2) {
        printf("%d ", *(arr + i));
    }
    printf("\n");
}
