/* 
Answer For A:
    myGrades:
    80   0   0   0   0   0   0   0   0   0   0
    60   0   0   0   0   0   0   0   0   0   0
    70   0   0   0   0   0   0   0   0   0   0
*/
// Answer For B: The Problem In Array Was That It Is Not A 2D Array But A 1d, And Daniel Wanted It To Be 2D, So i Fixed It And Added An Elegant Print To It Using For Loops.
#include <stdio.h>

#define COURSES 3
#define EXERCISES 11

int main(void) 
{
	int i = 0;
	int j = 0;
    int myGrades[COURSES][EXERCISES] = { {80},{60},{70} };
    for (i = 0; i < COURSES; i++) 
	{
        printf("%d|", i + 1);
        for (j = 0; j < EXERCISES; j++) 
		{
            printf("%3d ", myGrades[i][j]);
        }
        printf("\n");
    }

    return 0;
}
