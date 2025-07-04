#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int copyTextFile(FILE *src, FILE *dest);
int copyBinaryFile(FILE *src, FILE *dest);
int askOverwritePermission(const char *filename);

int main(int argc, char *argv[]) 
{
    if (argc != 4) 
    {
        printf("Error: You must provide three arguments: <textCopy|binaryCopy> <source> <destination>\n");
        return 1;
    }

    const char *mode = argv[1];
    const char *srcPath = argv[2];
    const char *destPath = argv[3];
    int isText = 0;

    if (strcmp(mode, "textCopy") == 0) 
    {
        isText = 1;
    } 
    else if (strcmp(mode, "binaryCopy") != 0) 
    {
        printf("Error: First argument must be either textCopy or binaryCopy.\n");
        return 1;
    }

    const char *srcMode = NULL;
    if (isText)
    {
        srcMode = "r";
    }
    else
    {
        srcMode = "rb";     
    }
    FILE *srcFile = fopen(srcPath, srcMode);
    if (!srcFile) 
    {
        printf("Error: Cannot open source file \"%s\".\n", srcPath);
        return 1;
    }

    // Check if destination file exists
    FILE *testDest = fopen(destPath, "r");
    if (testDest) 
    {
        fclose(testDest);
        if (!askOverwritePermission(destPath)) 
        {
            fclose(srcFile);
            printf("Copy canceled by user.\n");
            return 0;
        }
    }
    const char *destMode = 0;
    if (isText)
    {
        destMode = "w";
    }
    else
    {
        destMode = "wb";
    }
    
    FILE *destFile = fopen(destPath, destMode);
    if (!destFile) 
    {
        fclose(srcFile);
        printf("Error: Cannot open destination file \"%s\" for writing.\n", destPath);
        return 1;
    }

    int success = 0;
    if (isText)
    {
        success = copyTextFile(srcFile, destFile);
    }
    else
    {
        success = copyBinaryFile(srcFile, destFile);
    }

    fclose(srcFile);
    fclose(destFile);

    if (success) 
    {
        printf("File copied successfully.\n");
    } 
    else
    {
        printf("Error occurred during copy.\n");
        return 1;
    }

    return 0;
}

// Function to copy text file
int copyTextFile(FILE *src, FILE *dest) 
{
    int ch = 0;
    while ((ch = fgetc(src)) != EOF) 
    {
        if (fputc(ch, dest) == EOF) 
        {
            return 0;
        }
    }
    return 1;
}

// Function to copy binary file
int copyBinaryFile(FILE *src, FILE *dest)
{
    char buffer[1024] = {0};
    size_t bytesRead = 0;
    while ((bytesRead = fread(buffer, 1, sizeof(buffer), src)) > 0) 
    {
        if (fwrite(buffer, 1, bytesRead, dest) != bytesRead)
        {
            return 0;
        }
    }
    return 1;
}

// Ask user whether to overwrite existing file
int askOverwritePermission(const char *filename) 
{
    char response[10] = {0};
    printf("File \"%s\" already exists. Overwrite? (y/n): ", filename);
    if (fgets(response, sizeof(response), stdin)) 
    {
        return (response[0] == 'y' || response[0] == 'Y');
    }
    return 0;
}
