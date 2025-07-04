#include <stdio.h>
#include <string.h>

void decrypt(char* cipher, int n);
#define SIZE 100
int main() 
{
    char text[SIZE] = "";
    int shift = 0;
    printf("Please enter a string to decrypt: ");
    fgets(text,SIZE, stdin);
    printf("Please enter the number of letters to shift: ");
    scanf("%d", &shift);
    decrypt(text, shift);
    printf("Decrypted text: %s\n", text);
    
    return 0;
}
/*
function to decrypt a string
input: char* cipher - the string to decrypt, int n - the number of letters to shift
output: void
*/
void decrypt(char* cipher, int n) 
{
    int len = strlen(cipher);
    char* start = cipher;
    char* end = cipher + len - 1;
    
    while (start < end) 
    {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
    
    for (char* ptr = cipher; *ptr; ptr++) 
    {
        if (*ptr >= 'a' && *ptr <= 'z')
        {
            *ptr = 'a' + (*ptr - 'a' + n) % 26;
        }
    }
}
