#include <stdio.h>

// Function prototypes
void printJoke(int jokeType);
int userChoice();

int main()
{
    int choice = 1;
    do
    {
        // Get the user's choice of joke type
        choice = userChoice();
        if (choice != 0) // 0 indicates the user wants to exit
        {
            printJoke(choice);
            printf("\nPress Enter to continue...\n");
            getchar(); // Consume the newline left by scanf
            getchar(); // Wait for user input to continue
        }
    }
	while (choice != 0);

    printf("\nGoodbye! Thanks for using the joke program.\n");
    return 0;
}

// Function to display joke options and get the user's choice
int userChoice()
{
    int choice;

    // Display menu
    printf("\nChoose a type of joke:\n");
    printf("1. Programmer Joke\n");
    printf("2. Nature Joke\n");
    printf("3. Food Joke\n");
    printf("0. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    // Validate choice
    if (choice < 0 || choice > 3)
    {
        printf("\nInvalid choice! Please choose between 0 and 3.\n");
        return userChoice(); // Recursively ask again for valid input
    }

    return choice;
}

// Function to print the joke based on the chosen type
void printJoke(int jokeType)
{
    switch (jokeType)
    {
        case 1:
            printf("\nWhy do programmers prefer dark mode?\nBecause light attracts BUGS!!\n");
            break;
        case 2:
            printf("\nWhy don’t mountains ever get tired?\nBecause they’re always peaking!!\n");
            break;
        case 3:
            printf("\nWhy did the tomato turn red?\nBecause it saw the salad dressing!!\n");
            break;
        default:
            printf("\nSomething went wrong! Please try again.\n");
            break;
    }
}
