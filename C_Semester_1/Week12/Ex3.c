#include <stdio.h>
#include <string.h>
#include <ctype.h>
//The Main Function
int is_valid_password(char *password);
int main()
{
    char password[50] = {0};
    printf("Enter password: ");
    scanf("%49s", password);

    if (is_valid_password(password)) 
	{
        printf("Yes\n");
    } 
	else 
	{
        printf("The password is not valid.\n");
    }

    return 0;
}
/*
This function checks if the given password is valid.
A valid password:
Has a length between 6 and 8 characters
Contains at least one digit
Contains at least one lowercase letter
Contains at least one uppercase letter
Does not contain consecutive identical characters
Input: the input password string.
Output: 1 if the password is valid, 0 otherwise.
*/
int is_valid_password(char *password) 
{
    int length = strlen(password);
    if (length < 6 || length > 8)
	{
        return 0;
    }

    int has_digit = 0, has_lower = 0, has_upper = 0;
	int i = 0;
    for (i = 0; i < length; i++) 
	{
        if (isdigit(password[i]))
		{
			has_digit = 1;
		}
        if (islower(password[i])) 
		{
			has_lower = 1;
		}
        if (isupper(password[i])) 
		{	
			has_upper = 1;
		}
        if (i > 0 && password[i] == password[i - 1]) 
		{
            return 0;
        }
    }

    return has_digit && has_lower && has_upper;
}
