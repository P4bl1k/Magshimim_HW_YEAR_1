#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int fibonacci(int num, int* a);
int fibonacci2(int n, int* memo, int* a);
int main()
{
    int counter = 0;
    int memo[100] = {0};//For B
    int* pCounter = &counter;
    int number = 0;
    int result = 0;
    printf("Please Enter A Number: ");
    scanf("%d",&number);
    result = fibonacci(number,pCounter);
    printf("Number = %d, calls = %d\n",result,counter);
    //Answer For B:
    counter = 0;
    for (int i = 0; i < 100; i++) 
    {
        memo[i] = -1;
    }
    result = fibonacci2(number, memo, &counter);
    printf("Number = %d, calls = %d\n", result, counter);
    getchar();
    return 0;
}


int fibonacci(int num, int* a)
{
    (*a)++;
    if(num <= 1)
    {
        return num;
    }
    return fibonacci(num - 1,a) + fibonacci(num - 2, a);
}

int fibonacci2(int n, int* memo, int* a) 
{
    (*a)++;
    if (n <= 1)
    {
        return n;
    }
    if (memo[n] != -1)
    {
        return memo[n];
    }
    memo[n] = fibonacci2(n - 1, memo, a) + fibonacci2(n - 2, memo, a);
    return memo[n];
}
// ANSWER FOR A: if 5: Num(Fibonacci) = 5, Counter = 15
// if 7: Num(Fibonacci) = 13, Counter = 41

// ANSWER FOR B: if 5: Num(Fibonacci) = 5, Counter = 9
// if 7: Num(Fibonacci) = 13, Counter = 13
