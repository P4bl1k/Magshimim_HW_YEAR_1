#include <stdio.h>

int main(void) {
    const int minAge = 16;
    const int maxAge = 18;
    int age = 0;

    printf("Please enter an age:\n");
    scanf("%d", &age);
    getchar();

    if (age >= minAge && age <= maxAge) {
        printf("Sorry, no phone for you...\n");
    } else {
        printf("Yay! Your age not between 16 and 18!\n");
        printf("You can have a phone!\n");
    }

    return 0;
}