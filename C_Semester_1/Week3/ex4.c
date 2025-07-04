#include <stdio.h>
int main()
{
	int i = 65537;
	unsigned short s = (unsigned short)i;
	float f = (float)i;
	char c = (char)i;
	printf("s = %hu, i = %d , f = %f , c = %c",s,i,f,c);
	return (0);
}
