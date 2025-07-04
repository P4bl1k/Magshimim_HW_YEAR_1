#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void printUsage();

int main(int argc, char* argv[]) 
{
    if (argc < 4) 
    {
        printf("ERROR! Invalid Number of Arguments!\n");
        printUsage();
        getchar();
        return 1;
    }

    char* command = argv[1];
    int result = 0;
    if (strcmp(command, "ADD") == 0) 
    {
        result = 0;
        for (int i = 2; i < argc; i++) 
        {
            result += atoi(argv[i]);
        }
    } 
    else if (strcmp(command, "MUL") == 0) 
    {
        result = 1;
        for (int i = 2; i < argc; i++) 
        {
            result *= atoi(argv[i]);
        }
    } 
    else 
    {
        printf("ERROR! Invalid Command!\n");
        printUsage();
        getchar();
        return 1;
    }

    printf("Result: %d\n", result);
    getchar();
    return 0;
}
void printUsage()
{
    printf("Usage: [ADD | MUL] <number>,<number>\n");
}
