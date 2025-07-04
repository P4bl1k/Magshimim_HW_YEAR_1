#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

bool isValidQuadraticEquation(char str[]);

int main() 
{
    char input[100] = {0};  // Array to store input equation

    printf("Enter a quadratic equation (Ax^2 + Bx + C = 0): ");
    fgets(input, sizeof(input), stdin);
    
    // Remove the trailing newline character
    input[strcspn(input, "\n")] = '\0';

    if (isValidQuadraticEquation(input))
    {
        printf("Valid quadratic equation!\n");
    } 
    else 
    {
        printf("Invalid quadratic equation.\n");
    }

    return 0;
}

bool isValidQuadraticEquation(char str[]) 
{
    int a = 0, b = 0, c = 0, zero = 0;
    char var1 = ' ', sign1 = ' ', sign2 = ' ', sign3 = ' ';

    // Extract values without using pointers
    if (sscanf(str, "%d%c^2 %c %dx %c %d %c %d", &a, &var1, &sign1, &b, &sign2, &c, &sign3, &zero) == 8)
    {
        // Validate extracted components
        if (var1 == 'x' && (sign1 == '+' || sign1 == '-') && (sign2 == '+' || sign2 == '-') && sign3 == '=' && zero == 0)
        {
            return true;
        }
    }
    return false;
}
