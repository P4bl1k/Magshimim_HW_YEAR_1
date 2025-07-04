#include <stdio.h>

#define ROWS 11
#define COLS 11

void TheMultiplicatonTable(int str[][COLS]); 

// The Main Function
int main()  
{     
    int input[ROWS][COLS] = {0};  // Corrected array declaration
    TheMultiplicatonTable(input);
    return 0;
}  

void TheMultiplicatonTable(int str[][COLS])  
{     
    int i = 0,j = 0;
    for (i = 1; i < ROWS; i++)  
    { 
        for (j = 1; j < COLS; j++) 
        { 
            str[i][j] = i * j;
			if(i*j != 100)
			{
				printf("%3d ", str[i][j]);
			}
			else
			{
				printf("%2d", str[i][j]);
			}
        } 
        printf("\n");     
    } 
}
