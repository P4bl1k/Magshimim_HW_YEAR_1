/*
TimeLine:
1: Welcoming and Printing The Instructions For The Game
2: Showing The Difficulty Levels
3: Choosing Difficulty Level
4: Generate The Secret Code with Min_Value and Max_Value
5: Entering 4-lengthed code
6: Validating it with Length and Min_Value+Max_Value Validation
7: After Validation Analyzing the Guess With The Secret Code
8: Answering the Player With Exact And Partial Matches 
9: If Correct Answer Or Tries have ended, Give "You Win!" or "You Lost!" and Ask To Play Again
10: If Y, Go To 2nd, IF N, End Code
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define CODE_LENGTH 4
#define MIN_VALUE 1
#define MAX_VALUE 6

int exactMatches = 0;
int partialMatches = 0;

// Functions
void printInstructions();
int generateSecretCode();
bool hasDuplicateDigits(int number);
bool isValidGuess(int guess);
void analyzeGuess(int secretCode, int guess);
int readInputWithoutEnter(int attempt,int choice);
void playGame(int attempts, int choice);

// Main Function
int main() 
{
    char playAgain = ' ';
    srand((unsigned int)time(NULL));
    int choice = 0;

    while (1) 
    {
        printInstructions();
        printf("Choose Difficulty Level:\n");
        printf("1) Easy (20 rounds)\n");
        printf("2) Moderate (15 rounds)\n");
        printf("3) Hard (10 rounds)\n");
        printf("4) Crazy (random number of rounds 5-25)\n");
        printf("Make a choice: ");
        scanf("%d", &choice);

        int attempts = 0;
        switch (choice) 
        {
            case 1: 
                attempts = 20;
                break;
            case 2: 
                attempts = 15; 
                break;
            case 3:
                attempts = 10;
                break;
            case 4: 
                attempts = (rand() % 21) + 5; 
                break;
            default: 
                printf("Illegal Choice, Try Again!\n");
                continue;
        }

        playGame(attempts,choice);

        printf("Would you like to play again? (y/n): ");
        while (1) 
        {
            playAgain = getch(); // Read input without Enter
            printf("%c\n", playAgain); // Show the input for user feedback
            if (playAgain == 'y' || playAgain == 'n') 
            {
                break;
            } 
            else 
            {
                printf("\nWould you like to play again? (y/n): ");
            }
        }

        if (playAgain == 'n') 
        {
            printf("Thanks for playing!\n");
            break;
        }
    }

    return 0;
}
/* Function To Output Instructions
Input: None
Output: None
*/
void printInstructions() 
{
    printf("Welcome to \"MAGSHIMIM CODE-BREAKER!!!\n\n");
    printf("A secret password was chosen to protect the credit card of Pancratius,\n");
    printf("the descendant of Antiochus.\n");
    printf("Your mission is to stop Pancratius by revealing his secret password.\n");
    printf("\nThe rules are as follows:\n");
    printf("1. In each round you try to guess the secret password (4 distinct digits)\n");
    printf("2. After every guess you'll receive two hints about the password\n");
    printf("   HITS:   The number of digits in your guess which were exactly right.\n");
    printf("   MISSES: The number of digits in your guess which belongs to\n");
    printf("           the password but were misplaced.\n");
    printf("3. If you'll fail to guess the password after a certain number of rounds\n");
    printf("   Pancratius will buy all the gifts for Hanukkah!!!\n");
}

/* Function To Generate Secret Code
Input: None
Output: Secret Code
*/
int generateSecretCode() 
{
    int code = 0;
    int multiplier = 1;

    while (code == 0 || hasDuplicateDigits(code)) 
    {
        code = 0;
        multiplier = 1;
		int i = 0;
        for (i = 0; i < CODE_LENGTH; i++) 
        {
            int digit = 0;
            bool unique = true;

            do 
            {
                digit = (rand() % MAX_VALUE) + MIN_VALUE;
                unique = true;
                int temp = code;

                while (temp > 0) 
                {
                    if (temp % 10 == digit) 
                    {
                        unique = false;
                        break;
                    }
                    temp = temp / 10;
                }

            } 
            while (!unique);

            code = code + digit * multiplier;
            multiplier = multiplier * 10;
        }
    }

    return code;
}

/* Function to validate a guess as it does not have duplicate digits
Input: The Guess Of User
Output: True OR False
*/
bool hasDuplicateDigits(int number) 
{
    while (number > 0) 
    {
        int digit = number % 10;
        int temp = number / 10;

        while (temp > 0) 
        {
            if (temp % 10 == digit) 
                return true;
            temp = temp / 10;
        }

        number /= 10;
    }

    return false;
}

/* Function to validate a guess as a 4-digit integer
Input: The Guess Of User
Output: True OR False
*/
bool isValidGuess(int guess) 
{
    if (hasDuplicateDigits(guess)) return false;

    int count = 0;
    while (guess > 0) 
    {
        int digit = guess % 10;
        if (digit < MIN_VALUE || digit > MAX_VALUE) 
        {
            return false;
        }
        guess /= 10;
        count++;
    }

    return count == CODE_LENGTH;
}

/* Function to Analyze Your Guess
Input: The generated code, the user's guess
Output: None
*/
void analyzeGuess(int secretCode, int guess) 
{
    int tempSecret = secretCode;
    int tempGuess = guess;
	int i = 0;
    exactMatches = 0;
    partialMatches = 0;

    for (i = 0; i < CODE_LENGTH; i++) 
    {
        int secretDigit = tempSecret % 10;
        int guessDigit = tempGuess % 10;

        if (secretDigit == guessDigit) 
        {
            exactMatches++;
        } 
        else 
        {
            int temp = secretCode;
            while (temp > 0) 
            {
                if (temp % 10 == guessDigit) 
                {
                    partialMatches++;
                }
                temp = temp / 10;
            }
        }
        tempSecret /= 10;
        tempGuess /= 10;
    }
}
/* Function to read input without pressing Enter
Input:none
Output:Input of a user
*/
int readInputWithoutEnter(int attempt,int choice)
{
    int input = 0;
	int i = 0;
    printf("Write your guess (only 1-6, no ENTER is needed)\n");
	if(choice == 4)
	{
		printf("CRAZY MODE!!!\n");
	}
	else
	{
		printf("%d Guesses left\n",attempt);
	}
    for (i = 0; i < CODE_LENGTH; i++) 
    {
        char c = getch(); // Read one character without Enter
        if (c >= '0' && c <= '9') 
        {
            input = input * 10 + (c - '0');
            printf("%c", c); // Show the character
        }
    }
    printf("\n");
    return input;
}
/* Function For Main GamePlay
Input: Attempts Amount
Output: None
*/
void playGame(int attempts, int choice)
{
    int secretCode = generateSecretCode();
	int attempt = 0;
    printf("Secret Code Generated, Now Guess it!\n");

    for (attempt = attempts; attempt > 0; attempt--) 
    {
        int guess = readInputWithoutEnter(attempt,choice);

        if (!isValidGuess(guess)) 
        {
            printf("Only 1-6 are allowed, try again!\n");
			attempt++;
        }
        else
        {
            analyzeGuess(secretCode, guess);

            if (exactMatches == CODE_LENGTH) 
            {
				int total = attempts - attempt;
                printf("   4 HITS YOU WON!!!\n");
				printf("It took you only %d guesses, you are a professional code breaker!\n",total);
                break;
            } 
            else 
            {
                printf("You got    %d HITS    %d MISSES\n", exactMatches, partialMatches);
            }
        }

        if (attempt == 1) 
        {
            printf("OOOOHHHH!!! Pancratius won and bought all of Hanukkah's gifts.\nNothing left for you...\n");
            printf("The secret password was %d\n",secretCode);
        }
    }
}
