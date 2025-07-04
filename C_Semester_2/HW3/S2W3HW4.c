/*********************************
* Class: MAGSHIMIM C2			 *
* Week 3           				 *
* HW solution   			 	 *
**********************************/
#include <stdio.h>
#include <string.h>

void printArray(char* p, int len)
{
    char* end = p + len - 1;
	for( p ; p < end ; p++ ) 
	{
		printf("%c", *p);
	}
	printf("\n");
}
// The Bug was in the printArray function, where the loop condition was incorrect.
// The correct condition should be p < end, not p <= p + len,It Should be one less than p+len.
int main(void)
{
	char* msg = "hi jyegq meet me at 2 :)";
	printArray(msg, strlen(msg));
    getchar();
	return 0;
 }