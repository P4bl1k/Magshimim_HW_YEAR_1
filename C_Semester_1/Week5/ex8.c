#include <stdio.h>
int main()
{
    char input = ' ';
    scanf("%c", &input);
    (input == 'C') ? printf("UPPER") : 
    (input == 'c') ? printf("LOWER") : 
	printf("illegal character");
    return 0;
}