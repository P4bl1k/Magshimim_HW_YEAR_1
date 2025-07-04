#include <stdio.h>
#include <conio.h>

#define PI 3.1415926535
int main()
{
	float radius = 0;
	printf("Enter The radius of a Ball:");
	scanf("%f",&radius);
	printf("The Area Of the ball is:%f", 4*PI*radius*radius);
	
    return 0;
}
