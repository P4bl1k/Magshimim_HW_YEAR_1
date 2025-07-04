#include <stdio.h>
#include <string.h>
#include <ctype.h>

void remove_spaces(char *str);
int is_palindrome(char *str);

//The Main Function
int main() 
{
    char input[100] = {0};
    printf("Enter String:");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove newline character

    remove_spaces(input);

    if (is_palindrome(input)) 
	{
        printf("Yes,It Is Palindrome\n");
    } else 
	{
        printf("No,It isnt Palindrome\n");
    }

    return 0;
}
/*
Function: remove_space
This function removes all spaces from the input string.
input: the input string to be modified.
output:string via no spaces.
*/
void remove_spaces(char *str) 
{
    int i = 0;
	int j = 0;
    for (i = 0; str[i] != '\0'; i++)
	{
        if (str[i] != ' ') 
		{
            str[j++] = str[i];
        }
    }
    str[j] = '\0';
}

/*
function checks if a given string is a palindrome.
It compares characters from both ends moving towards the center.
Input: the input string without spaces.
Output: 1 if the string is a palindrome, 0 otherwise.
*/
int is_palindrome(char *str) 
{
    int len = strlen(str);
	int i = 0;
    for (i = 0; i < len / 2; i++) 
	{
        if (str[i] != str[len - i - 1]) 
		{
            return 0;
        }
    }
    return 1;
}
