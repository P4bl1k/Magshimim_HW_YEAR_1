//DONE
#include <stdio.h>

// Enumerations for months and weekdays
enum Month { JAN = 1, FEB, MAR, APR, MAY, JUN, JUL, AUG, SEP, OCT, NOV, DEC };
enum Weekday { SUN = 1, MON, TUE, WED, THU, FRI, SAT };

int checkInput(int month, int day);
int calculateDayOfWeek(int month, int day, int firstDayOfMonth);
int main() {
    int month, day, firstDayOfMonth;

    // Input validation loop for month and day
    do {
        printf("Enter the month (1-12): ");
        scanf("%d", &month);
        printf("Enter the day (1-31): ");
        scanf("%d", &day);

        if (!checkInput(month, day)) {
            printf("Invalid date. Please reenter.\n");
        }
    } 
    while (!checkInput(month, day));

    // Input validation loop for the first day of the month
    do 
    {
        printf("Enter the first day of the month (1=Sun, 7=Sat): ");
        scanf("%d", &firstDayOfMonth);

        if (firstDayOfMonth < 1 || firstDayOfMonth > 7) {
            printf("Invalid first day. Please reenter.\n");
        }
    } 
    while (firstDayOfMonth < 1 || firstDayOfMonth > 7);

    int result = calculateDayOfWeek(month, day, firstDayOfMonth) - 2;

    if (result == -1)
    {
        printf("The day of the week is: Sunday\n");
    }
    else if (result == 0) 
    {
        printf("The day of the week is: Monday\n");
    }
    else if (result == 1) 
    {
        printf("The day of the week is: Tuesday\n");
    } 
    else if (result == 2)
    {
        printf("The day of the week is: Wednesday\n");
    }
    else if (result == 3)
    {
        printf("The day of the week is: Thursday\n");
    }
    else if (result == 4) 
    {
        printf("The day of the week is: Friday\n");
    }
    else 
    {
        printf("The day of the week is: Saturday\n");
    }

    return 0;
}

// Function to check if the input date is valid
// input: number of month, number of day
// output: true of false
int checkInput(int month, int day) 
{
    int daysInMonth;
    switch (month)
    {
        case JAN: case MAR: case MAY: case JUL: case AUG: case OCT: case DEC:
            daysInMonth = 31;
            break;
        case APR: case JUN: case SEP: case NOV:
            daysInMonth = 30;
            break;
        case FEB:
            daysInMonth = 28;
            break;
        default:
            return 0;
    }

    if (day < 1 || day > daysInMonth)
    {
        return 0;
    }
    return 1;
}

// Function to calculate the day of the week
// input: month,day,first day of the month
// output: day of the week number
int calculateDayOfWeek(int month, int day, int firstDayOfMonth) 
{
    int dayOfWeek = (firstDayOfMonth + (day - 1)) % 7;
    if (dayOfWeek == 0) 
    {
        dayOfWeek = 7;
    }
    return dayOfWeek;
}
