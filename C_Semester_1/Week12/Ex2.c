#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void int_to_string(int num, char str[]);

int main() 
{
    int num = 0;
    char str[20] = {0};  // Array to store the converted number
    
    // Prompt user for an integer input
    printf("Enter an integer: ");
    scanf("%d", &num);
    
    // Convert integer to string
    int_to_string(num, str);
    
    // Print the length and content of the string
    if (num > 0)
    {
        printf("String representation: +%s\n", str);
        printf("Length of the string: %lu\n", strlen(str) + 1); // Include the '+' sign
    }
    else
    {
        printf("String representation: %s\n", str);
        printf("Length of the string: %lu\n", strlen(str)); // No extra sign for negatives
    }
    
    return 0;
}

// Function to convert an integer to a string manually
void int_to_string(int num, char str[]) 
{
    int is_negative = 0, i = 0;
    
    // Handle negative numbers
    if (num < 0) 
    {
        is_negative = 1;
        num = -num;  // Convert to positive for easier processing
    }

    // Extract digits and store them in reverse order
    do 
    {
        str[i++] = (num % 10) + '0';  // Convert digit to character
        num /= 10;
    } while (num > 0);

    // Add negative sign if needed
    if (is_negative) 
    {
        str[i++] = '-';
    }

    str[i] = '\0';  // Null-terminate the string

    // Reverse the string to get the correct order
    int left = 0, right = i - 1;
    while (left < right) 
    {
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}
