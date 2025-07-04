#include <stdio.h>

struct menuItem1 
{
    char isSpicy; 
    float price;  
    char name[7];  
};

struct menuItem2 
{
    char name[7];   
    char isSpicy; 
    float price;
};

int main() 
{
    printf("Size of menuItem1: %d bytes\n", sizeof(struct menuItem1));
    printf("Size of menuItem2: %d bytes\n", sizeof(struct menuItem2));
    return 0;
}

//Answer of A: The first one takes more Space Because when Float is needed it need to furfill that completes
//to number that can be divided by 4, so it makes from 5 to 8 bytes, but in second one it is 
// dividing by four (12) so no need to be furfiiled.

//Answer for C: Yep, I was Right ;))