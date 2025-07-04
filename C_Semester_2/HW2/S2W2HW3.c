#include <stdio.h>

void Swap(float* Num1, float* Num2);

int main()
{
    float Num1 = 0;
    float Num2 = 0;
    float* PN1 = &Num1;
    float* PN2 = &Num2;
    scanf("%f",&Num1);
    scanf("%f",&Num2);
    Swap(PN1,PN2);
    printf("After The Swap: %f %f",Num1,Num2);
    return 0;
}
void Swap(float* Num1, float* Num2)
{
    float temp = *Num1;
    *Num1 = *Num2;
    *Num2 = temp;
}
