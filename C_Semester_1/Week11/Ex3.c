#include <stdio.h>
#include <stdbool.h>

#define NUM_GUESTS 200

float calculateAverageAge(int ages[], int size);
int countChildren(int ages[], int size);
bool isAgePresent(int ages[], int size, int ageToFind);
bool hasAgePair(int ages[], int size, int ageToFind);
int findYoungest(int ages[], int size);
int findOldest(int ages[], int size);
// The Array OF Guests
int guestAges[NUM_GUESTS] =
{
	42, 108, 95, 101, 90, 5, 79, 79, 83, 105, 66, 66, 2, 28, 2, 12, 116, 63, 28, 37,	
					 112, 85, 63, 34, 53, 23, 22, 117, 39, 96, 48, 7, 12, 19, 70, 113, 108, 20, 116,
					 55, 24, 52, 3, 94, 34, 105, 22, 32, 54, 29, 108, 45, 23, 118, 118, 20, 84, 22,
					 50, 59, 77, 36, 111, 43, 49, 107, 41, 63, 65, 89, 87, 46, 51, 10, 11, 111, 7, 22,
					 34, 69, 70, 24, 85, 35, 37, 81, 47, 57, 12, 29, 25, 40, 27, 44, 18, 59, 39, 43, 
					 10, 102, 34, 36, 80, 19, 25, 91, 100, 27, 114, 67, 102, 66, 45, 113, 31, 70, 18, 
					 94, 58, 73, 107, 91, 42, 37, 36, 48, 16, 95, 72, 53, 111, 71, 22, 5, 47, 71, 28, 
					 72, 8, 58, 98, 48, 34, 64, 66, 30, 50, 39, 102, 109, 63, 107, 27, 71, 94, 9,
					 61, 72, 43, 96, 11, 120, 25, 18, 69, 4, 116, 82, 3, 111, 92, 117, 15, 101, 37, 22, 
					 109, 40, 109, 5, 2, 55, 54, 80, 19, 99, 61, 69, 8, 108, 9, 14, 49, 44, 48, 22, 
					 31, 18, 14, 35
};
// Main Function
int main() 
{
    printf("Average age: %.2f\n", calculateAverageAge(guestAges, NUM_GUESTS));
    printf("Number of children (12 or younger): %d\n", countChildren(guestAges, NUM_GUESTS));

    int searchAge = 0;
    printf("Enter an age to check presence: ");
    scanf("%d", &searchAge);
    if (isAgePresent(guestAges, NUM_GUESTS, searchAge)) 
	{
        printf("Yes, there is at least one guest aged %d.\n", searchAge);
    } 
	else 
	{
        printf("No guests found with age %d.\n", searchAge);
    }

    printf("Enter an age to check for pairs: ");
    scanf("%d", &searchAge);
    if (hasAgePair(guestAges, NUM_GUESTS, searchAge)) 
	{
        printf("Yes, there are at least two guests aged %d.\n", searchAge);
    } 
	else 
	{
        printf("No pairs found with age %d.\n", searchAge);
    }

    printf("Youngest guest age: %d\n", findYoungest(guestAges, NUM_GUESTS));
    printf("Oldest guest age: %d\n", findOldest(guestAges, NUM_GUESTS));

    return 0;
}

/*
Function To Find The Average Age OF All The Members
input: The Ages Of The Members and Amount Of Members
output: The Average Age Of All The Members
*/
float calculateAverageAge(int ages[], int size)
{
    int sum = 0;
	int i = 0;
    for (i = 0; i < size; i++) 
	{
        sum += ages[i];
    }
    return ((float)sum / size);
}
/*
Function To Find The Amount Of People That are Less Than 12 Years Old
input: The Ages Of The Members and Amount Of Members
output: The Amount Of People That are Less Than 12 Years Old
*/
int countChildren(int ages[], int size)
{
    int count = 0;
	int i = 0;
    for (i = 0; i < size; i++)
	{
        if (ages[i] <= 12) 
		{
            count++;
        }
    }
    return count;
}
/*
Function To Find The Number That User Asked For
input: The Ages Of The Members,Amount Of Members and The Age TO Find
output: True or False
*/
bool isAgePresent(int ages[], int size, int ageToFind)
{
	int i = 0;
    for (i = 0; i < size; i++) 
	{
        if (ages[i] == ageToFind)
		{
            return true;
        }
    }
    return false;
}
/*
Function To Find If The List Have Pair OF Numbers That User Asked For
input: The Ages Of The Members,Amount Of Members and The Age TO Find
output: True or False
*/
bool hasAgePair(int ages[], int size, int ageToFind) 
{
    int count = 0;
	int i = 0;
    for (i = 0; i < size; i++) 
	{
        if (ages[i] == ageToFind)
		{
            count++;
            if (count == 2)
			{
                return true;
            }
        }
    }
    return false;
}
/*
Function To Find The Youngest Member Of The Party
input: The Ages Of The Members and Amount Of Members
output: The Age Of Youngest Member
*/
int findYoungest(int ages[], int size) 
{
    int min = ages[0];
	int i = 0;
    for (i = 1; i < size; i++)
	{
        if (ages[i] < min) 
		{
            min = ages[i];
        }
    }
    return min;
}

/*
Function To Find The Oldest Member Of The Party
input: The Ages Of The Members and Amount Of Members
output: The Age Of Oldest Member
*/
int findOldest(int ages[], int size) 
{
    int max = ages[0];
	int i = 0;
    for (i = 1; i < size; i++)
	{
        if (ages[i] > max)
		{
            max = ages[i];
        }
    }
    return max;
}
