#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int lastTakenSeat(int cols, int people);

int main()
{
    int cols = 20, people = 20;
    printf("Last taken seat: %d\n", lastTakenSeat(cols, people));
    return 0;
}

 int lastTakenSeat(int cols, int people)
{
    return people%cols;
}