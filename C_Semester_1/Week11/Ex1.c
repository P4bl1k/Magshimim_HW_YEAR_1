#include <stdio.h>

#define SIZE 5

int main() 
{
    int array[SIZE] = {0};
    int offset = 0;
	int i = 0;
    printf("Enter %d numbers to array: ", SIZE);
    for (i = 0; i < SIZE; i++) 
	{
        scanf("%d", &array[i]);
    }
    printf("Enter offset (0 to %d): ", SIZE - 1);
    scanf("%d", &offset);
    if (offset < 0 || offset >= SIZE) 
	{
        printf("Invalid offset. Please run the program again.\n");
        return 1;
    }
    printf("Array with offset of %d: ", offset);
    for (i = 0; i < SIZE; i++) 
	{
        printf("%d ", array[(i + offset) % SIZE]);
    }
    printf("\n");

    return 0;
}
