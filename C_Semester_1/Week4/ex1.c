#include <stdio.h>
int main()
{
	char char1='H';
	char char2 = ' ';
	char char3 = ' ';
	printf("Please Enter a character:");
	char2=getchar();
	getchar();
	printf("Please Enter another character:");
	scanf("%c",&char3);
	printf("Value of Character NO1:%c\nCharacter + 1:%c\nNum of Character 1:%d\nSum of Values:%d\nSum First And Third :%d",char1,char1+1,(int)char1+char2+char3,(int)char1+char3);
    return 0;
}
