#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 100
#define ALPHABET_SIZE 26

void replace_most_frequent(char str[]);

int main(void) 
{
    char str[MAX_LEN] = {0};
    printf("Enter a string: ");
    fgets(str, MAX_LEN, stdin);
    str[strcspn(str, "\n")] = '\0';  // Remove newline character

    replace_most_frequent(str);

    printf("Changed string: %s\n", str);
    return 0;
}

void replace_most_frequent(char str[])
{
    int i;
    int freq[ALPHABET_SIZE] = {0};
    int max_freq = 0, second_max_freq = 0;
    char max_char = '\0', second_max_char = '\0';

    // Convert the string to lowercase and count frequency
    for (i = 0; str[i] != '\0'; i++) 
    {
        if (isalpha(str[i]))  // Check if it's a letter
        {
            char lower = tolower(str[i]);  // Convert to lowercase
            freq[lower - 'a']++;
        }
    }

    // Find the most and second most frequent characters
    for (i = 0; i < ALPHABET_SIZE; i++)
    {
        if (freq[i] > max_freq) 
        {
            second_max_freq = max_freq;
            second_max_char = max_char;
            max_freq = freq[i];
            max_char = 'a' + i;
        } 
        else if (freq[i] > second_max_freq && freq[i] < max_freq) 
        {
            second_max_freq = freq[i];
            second_max_char = 'a' + i;
        }
    }

    // Ensure we have a valid second most frequent character
    if (second_max_char == '\0') 
    {
        return;  // No second most frequent character, so exit
    }

    // Replace occurrences of the most frequent character with the second most frequent
    for (i = 0; str[i] != '\0'; i++) 
    {
        if (tolower(str[i]) == max_char) 
        {
            if (isupper(str[i]))
                str[i] = toupper(second_max_char);
            else
                str[i] = second_max_char;
        }
        else if (tolower(str[i]) == second_max_char) 
        {
            if (isupper(str[i]))
                str[i] = toupper(max_char);
            else
                str[i] = max_char;
        }
    }
}
