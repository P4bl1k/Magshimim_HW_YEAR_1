#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_OF_ROLLS 9999
#define NUM_OF_FACES 6

int main() 
{
    int counters[NUM_OF_FACES] = {0};
    int i = 0;
    srand(time(NULL));
    
    for (i = 0; i < NUM_OF_ROLLS; i++)
	{
        int roll = rand() % NUM_OF_FACES;  // Generate a random number between 0 and NUM_OF_FACES-1
        counters[roll]++;  // Increase the corresponding counter
    }
    
    for (i = 0; i < NUM_OF_FACES; i++) 
	{
        printf("Face %d: %d times\n", i + 1, counters[i]);
    }
    
    return 0;
}
