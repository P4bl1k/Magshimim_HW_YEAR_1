#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#define STRING_SIZE 50

bool isPalindrome(char str[], int beg, int end);

int main() 
{
    printf("Enter String: ");
    char str[STRING_SIZE] = {0};
    fgets(str, STRING_SIZE, stdin);
    str[strcspn(str, "\n")] = '\0';
    if (isPalindrome(str, 0, strlen(str) - 1)) 
    {
        printf("Yes\n");
    }
    else 
    {
        printf("No\n");
    }
	getchar();
    return 0;
}
//Function To Check If The String is Palindrome by using Recursion
bool isPalindrome(char str[], int beg, int end)
{
    if (beg >= end)
    { 
        return true;
    }
    if (str[beg] != str[end]) 
    {
        return false;
    }
    return isPalindrome(str, beg + 1, end - 1);
}
