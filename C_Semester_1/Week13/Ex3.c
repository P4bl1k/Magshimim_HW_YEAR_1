#include <stdio.h>
#include <string.h>

#define NAMES_COUNT 10
#define NAME_LENGTH 50

void getNames(char names[NAMES_COUNT][NAME_LENGTH]);
void printResults(char names[NAMES_COUNT][NAME_LENGTH]);

int main() 
{
    char names[NAMES_COUNT][NAME_LENGTH] = {0};
    getNames(names);
    printResults(names);

    return 0;
}

/*
Function To Enter The Names
input:Array That Can Contain the Strings
output:Array Via The Strings
*/
void getNames(char names[NAMES_COUNT][NAME_LENGTH]) 
{
	int i = 0;
    printf("Enter %d Names:\n", NAMES_COUNT);
    for (i = 0; i < NAMES_COUNT; i++) 
	{
        printf("Name %d: ", i + 1);
        fgets(names[i], NAME_LENGTH, stdin);
        names[i][strcspn(names[i], "\n")] = '\0'; 
    }
}
/*
Function to find the Longest,shortest,first in alphabet and last in the array of strings
input:array of strings
output:Longest,shortest,first in alphabet and last in the array of strings
*/
void printResults(char names[NAMES_COUNT][NAME_LENGTH]) 
{
    int longestIndex = 0, shortestIndex = 0;
    int firstIndex = 0, lastIndex = 0;
	int i = 0;
    for (i = 1; i < NAMES_COUNT; i++) {
        if (strlen(names[i]) > strlen(names[longestIndex])) 
		{
            longestIndex = i;
        }
        if (strlen(names[i]) < strlen(names[shortestIndex])) 
		{
            shortestIndex = i;
        }
        if (strcmp(names[i], names[firstIndex]) < 0) 
		{
            firstIndex = i;
        }
        if (strcmp(names[i], names[lastIndex]) > 0) 
		{
            lastIndex = i;
        }
    }

    printf("\nLongest name: %s\n", names[longestIndex]);
    printf("Shortest name: %s\n", names[shortestIndex]);
    printf("First In AlphaBetical Order: %s\n", names[firstIndex]);
    printf("Last In AlphaBetical Order: %s\n", names[lastIndex]);
}
