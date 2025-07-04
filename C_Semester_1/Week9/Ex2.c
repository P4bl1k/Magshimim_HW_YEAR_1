//DONE
#include <stdio.h>

// Define enum for difficulty levels
typedef enum 
{
    EASY = 1,
    MEDIUM,
    HARD
} difficultyLevel;

int main() 
{
    int choice;

    // Display difficulty options
    printf("Select Difficulty Level:\n");
    printf("1. Easy\n");
    printf("2. Medium\n");
    printf("3. Hard\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &choice);

    // Check user choice and display the selected level
    switch ((difficultyLevel)choice) 
	{
        case EASY:
            printf("You selected Easy difficulty.\n");
            break;
        case MEDIUM:
            printf("You selected Medium difficulty.\n");
            break;
        case HARD:
            printf("You selected Hard difficulty.\n");
            break;
        default:
            printf("Invalid choice. Please select a valid option.\n");
    }

    return 0;
}

