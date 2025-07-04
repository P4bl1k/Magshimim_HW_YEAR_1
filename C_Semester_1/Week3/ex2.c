#include <stdio.h>
int main()
{
	char firstLetter = 'A';
	char lastLetter = 'Z';
	//printed first letter
	printf("This Is the first letter of the alphabet:%c\n",firstLetter);
	//printed last letter
	printf("This Is the last letter of the alphabet:%c\n",lastLetter);
	//Then I did the ascii value of Z minus ascii value of A and then added one to add the missing Z.
	printf("This Is the amount of letters in the alphabet:%d",(lastLetter-firstLetter+1));
	return (0);
}
