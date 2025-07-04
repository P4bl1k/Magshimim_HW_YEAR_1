#include <stdio.h>
#include <string.h>

#define PASSWORD "maGshimim2017"
#define STR_LEN 16
#define FALSE 0
#define TRUE !FALSE

int main(void)
{
    int pass = FALSE;
    char buff[STR_LEN] = {0};

    printf("Enter the password: ");
    scanf("%s", buff);

    /*
    a) When running the program - If the user enters the correct password: "maGshimim2017"
    Output is: Correct Password Access given to the secret files
    If the user enters a wrong password (up to 16 characters):
    Output is:Wrong Password
    */

    /*
     b) If the user enters a password longer than 16 characters:
     The program suffers from a **buffer overflow**, because the input exceeds the size of `buff` (16 chars).
    */
    if (strcmp(buff, PASSWORD))
    {
        printf("Wrong Password \n");
    }
    else
    {
        printf("Correct Password \n");
        pass = TRUE;
    }

    if (pass)
    {
        printf("Access given to the secret files \n");
    }

    getchar();
    return 0;

    // c) To fix the bug and close the security vulnerability: use fgets(buff, sizeof(buff), stdin); for safer input.
}
