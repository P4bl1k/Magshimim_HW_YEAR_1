#include <stdio.h>
int* createArray();
void printArray(int* array, int size);

int main()
{
    int* myArray = createArray();
    printArray(myArray, 5);
    return 0;
}

int* createArray() 
{
    int arr[5] = {10, 20, 30, 40, 50};
    return arr;
}

void printArray(int* array, int size)
{
    for (int i = 0; i < size; i++) 
    {
        printf("arr[%d] = %d\n", i, array[i]);
    }
}
//The Problem thats happening its the bug that the pointer is pointing at the local variable
// and the printarray function cant find the elements of the myarray because its local variable
// from createArray