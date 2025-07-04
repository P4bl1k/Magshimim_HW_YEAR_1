#include <stdio.h>

void Swap(float* Num1, float* Num2);
void Sort(float* Num1,float* Num2,float* Num3);

int main()
{
float n1 = 0;
float n2 = 0;
float n3 = 0;
float* pn1 = &n1;
float* pn2 = &n2;
float* pn3 = &n3;
scanf("%f %f %f",pn1,pn2,pn3);
getchar();
Sort(pn1,pn2,pn3);
printf("After Sorting:%f,%f,%f",n1,n2,n3);
getchar();
return 0;
}

void Swap(float* Num1, float* Num2)
{
float temp = *Num1;
*Num1 = *Num2;
*Num2 = temp;
}

void Sort(float* Num1,float* Num2,float* Num3)
{
if(*Num2 < *Num1)
{
    Swap(Num1,Num2);
}
if(*Num2 > *Num3)
{
    Swap(Num2,Num3);
}
if (*Num1 > *Num2) //Another Check After Swap
{
    Swap(Num1, Num2);
}
}