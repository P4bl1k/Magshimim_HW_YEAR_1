#include <stdio.h>
#define XXX 1.0873

int main()
{
  int x=1;
  printf("Welcome to United Arab Emirates, how many ILS you have?\n");
  scanf("%d",&x);
  printf("You have %.2f Dirham\n", (float)XXX*x);

  return 0;
}
