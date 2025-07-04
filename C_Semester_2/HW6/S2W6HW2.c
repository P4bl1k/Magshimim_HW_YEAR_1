#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50

void swap(char** a, char** b);

int main() 
{
    int n = 0;
    printf("How many friends do you have? ");
    scanf("%d", &n);
    getchar();

    char** friends = (char**)malloc(n * sizeof(char*));
    if (friends == NULL) 
    {
        printf(":(, I Always doing this reaction for unlocated memory so this is my convention)).\n");
        return 1;
    }
    char buffer[MAX_NAME_LENGTH] = {0};
    for (int i = 0; i < n; i++) 
    {
        printf("Enter name of friend #%d: ", i + 1);
        fgets(buffer, MAX_NAME_LENGTH, stdin);

        // Remove newline character if present
        buffer[strcspn(buffer, "\n")] = '\0';

        friends[i] = (char*)malloc(strlen(buffer) + 1);
        if (friends[i] == NULL) 
        {
            printf("Memory allocation error for name.\n");
            return 1;
        }
        strcpy(friends[i], buffer);
    }

    // Sort names alphabetically
    for (int i = 0; i < n - 1; i++) 
    {
        for (int j = i + 1; j < n; j++) 
        {
            if (strcmp(friends[i], friends[j]) > 0) 
            {
                swap(&friends[i], &friends[j]);
            }
        }
    }

    // Print sorted names
    printf("\nFriends' names in alphabetical order:\n");
    for (int i = 0; i < n; i++) {
        printf("%s\n", friends[i]);
        free(friends[i]); // Free each name string
    }

    free(friends); // Free the array of pointers
	getchar();
    return 0;
}
void swap(char** a, char** b) 
{
    char* temp = *a;
    *a = *b;
    *b = temp;
}
/*
B:How much memory was allocated?
For each friend:
    You allocate one pointer (char*), typically 8 bytes on a 64-bit system.
    You allocate exactly the number of characters in their name +1 (for the '\0').
Example:
    Dan = 3 bytes (D, a, n) + \0 = 4 bytes

    Eli = 4 bytes

    Shira = 6 bytes

    Noam = 5 bytes
Total:
Pointers: 4 friends * 8 bytes = 32 bytes
Strings: 4 + 4 + 6 + 5 = 19 bytes
Total dynamic memory used: 32 + 19 = 51 bytes
The temporary buffer[50] is not counted in dynamic memory, it's stack memory.
*/