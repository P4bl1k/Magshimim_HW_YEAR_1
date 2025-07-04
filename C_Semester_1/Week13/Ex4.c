#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORDS 10
#define MAX_LENGTH 50
#define ALPHABET_SIZE 26

void getSentence(char words[MAX_WORDS][MAX_LENGTH], int wordCountArr[MAX_WORDS]);

int isPanagram(char words[MAX_WORDS][MAX_LENGTH], int wordCount);

int main() 
{
    char words[MAX_WORDS][MAX_LENGTH] = {0};
    int wordCountArr[MAX_WORDS] = {0};
    int wordCount = 0;
	int i = 0;

    getSentence(words, wordCountArr);
    
    for (i = 0; i < MAX_WORDS; i++) 
    {
        if (wordCountArr[i] == 1) 
        {
            wordCount++;
        }
    }

    if (isPanagram(words, wordCount)) 
    {
        printf("The sentence is a pangram!\n");
    } 
    else 
    {
        printf("The sentence is NOT a pangram.\n");
    }

    return 0;
}

void getSentence(char words[MAX_WORDS][MAX_LENGTH], int wordCountArr[MAX_WORDS]) 
{
	int i = 0;
	int j = 0;
    printf("Enter up to %d words (only lowercase letters):\n", MAX_WORDS);
	for (i = 0; i < MAX_WORDS; i++) 
	{
		printf("Word %d: ", i + 1);
		scanf("%s", words[i]);
		wordCountArr[i] = 1;

		int tempCount = 0;

		for (j = 0; j <= i; j++) 
		{
			if (wordCountArr[j] == 1) 
			{
				tempCount++;
			}
		}

		if (isPanagram(words, tempCount)) 
		{
			break;
		}
	}
}

int isPanagram(char words[MAX_WORDS][MAX_LENGTH], int wordCount) 
{
	int i = 0;
	int j = 0;
    int letterFlags[ALPHABET_SIZE] = {0};
    int uniqueLetters = 0;

    for (i = 0; i < wordCount; i++) 
    {
        for (j = 0; j < strlen(words[i]); j++) 
        {
            char ch = words[i][j];

            if (ch >= 'a' && ch <= 'z') 
            {
                int index = ch - 'a';

                if (letterFlags[index] == 0) 
                {
                    letterFlags[index] = 1;
                    uniqueLetters++;
                }
            }
        }
    }
    return uniqueLetters == ALPHABET_SIZE;
}
