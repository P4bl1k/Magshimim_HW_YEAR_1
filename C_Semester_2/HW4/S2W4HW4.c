/*********************************
* Class: MAGSHIMIM C2			 *
* Week 4           				 *
* HW solution   			 	 *
**********************************/

#include <stdio.h>
#include <stdlib.h>

int getValidIndex(int count);
int getValidAnswer();
int main() 
{
    int *answers = NULL;
    int count = 0;

    printf("Enter The Number Of People that Answered:");
    scanf("%d", &count);
    answers = (int*)malloc(count * sizeof(int));
    if (!answers) 
    {
        printf(":(\n");
        return 1;
    }

    for (int i = 0; i < count; i++) 
    {
        printf("Enter The Answer Number %d: (1-5): ", i + 1);
        answers[i] = getValidAnswer();
    }
    int option = 0;
    do {
        printf("\nEnter Your Choice:\n");
        printf("1: Check Avg\n");
        printf("2: Change Answer\n");
        printf("3: Add The Number Of People\n");
        printf("4: Print The Answer Distribution\n");
        printf("5: Exit\n");
        scanf("%d", &option);

        switch (option)
        {
            case 1: 
            {
                double sum = 0;
                for (int i = 0; i < count; i++) 
                {
                    sum += answers[i];
                }
                float avg = sum / count;
                printf("The Avg is %.2f\n",avg);
                break;
            }
            case 2: 
            {
                printf("What Answer You Want To Change? ", count);
                int index = getValidIndex(count);
                printf("Enter New Answer: ");
                answers[index] = getValidAnswer();
                break;
            }
            case 3: 
            {
                int more = 0;
                printf("How Much More Answers Do you Want To Add:");
                scanf("%d", &more);
                int *temp = realloc(answers, (count + more) * sizeof(int));
                if (!temp) 
                {
                    printf(":(\n");
                    break;
                }
                answers = temp;
                for (int i = 0; i < more; i++) 
                {
                    printf("Enter The New Answer For User Number %d: (1-5) ", count + i + 1);
                    answers[count + i] = getValidAnswer();
                }
                count += more;
                break;
            }
            case 4: 
            {
                int distribution[5] = {0};
                for (int i = 0; i < count; i++) 
                {
                    distribution[answers[i] - 1]++;
                }
                for (int i = 0; i < 5; i++) 
                {
                    printf("%d - %d\n", i + 1, distribution[i]);
                }
                break;
            }
            case 5:
                printf("Exiting Program\n");
                break;
            default:
                printf("Wrong Choice\n");
        }

    } 
    while (option != 5);
    free(answers);
    getchar();
	getchar();
    return 0;
}
/*
Function Is Entering Number and Checking If Its in range 1-5
input: Null
output: Valid Number
*/
int getValidAnswer()
{
    int answer = 0;
    while (1)
    {
        scanf("%d", &answer);
        if (answer >= 1 && answer <= 5) 
        {
            return answer;
        }
        printf("Answer Is Wrong,Change It To Value 1-5:");
    }
}

/*
Function To Enter Valid Index to the array
Input: The amount Of Numbers in array
output: Entered index
*/
int getValidIndex(int count) 
{
    int index = 0;
    while (1) 
    {
        scanf("%d", &index);
        if (index >= 1 && index <= count) 
        {
            return index - 1; 
        }
        printf("Number isn`t valid, It Should be between 1-%d", count);
    }
}