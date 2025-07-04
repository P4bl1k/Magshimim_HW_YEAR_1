/*********************************
* Class: MAGSHIMIM C1            *
* Week 11                        *
**********************************/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    // Add null terminators to the character arrays
    char str1[] = {'H', 'i', ' ', '\0'};
    char str2[] = {'H', 'o', '\0'};

    // Fix length calculation by using strlen(str2)
    strncat(str1, str2, strlen(str2));

    // Print the concatenated result
    printf("%s\n", str1);
    return 0;
}
