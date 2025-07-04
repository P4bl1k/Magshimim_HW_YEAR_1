#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LEN 1024

int countString(const char *filename, const char *target);

int main(int argc, char *argv[]) 
{
    if (argc != 2)
    {
        printf("Usage: %s <csv_file>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    int choice = 0;

    while (1) 
    {
        printf("\n--- CSV Menu ---\n");
        printf("1. Count string\n");
        printf("2. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 1) 
        {
            char search[MAX_LINE_LEN] = {0};
            printf("Enter string to count: ");
            scanf("%s", search);
            int result = countString(filename, search);
            if (result >= 0)
                printf("The string '%s' appeared %d times.\n", search, result);
        } 
        else if (choice == 2) 
        {
            return 0;
        } 
        else 
        {
            printf("Invalid choice!\n");
        }
    }

    return 0;
}

int countString(const char *filename, const char *target) 
{
    FILE *file = fopen(filename, "r");
    if (!file) 
    {
        printf("Error opening file!\n");
        return -1;
    }

    char line[MAX_LINE_LEN] = {0};
    int count = 0;

    while (fgets(line, sizeof(line), file)) 
    {
        char *token = strtok(line, ",\n");
        while (token) 
        {
            if (strcmp(token, target) == 0) 
            {
                count++;
            }
            token = strtok(NULL, ",\n");
        }
    }

    fclose(file);
    return count;
}

