//StillInProgress
#include <stdio.h>
#include <math.h>

typedef enum {
    CALC_DISTANCE = 1,
    CALC_HYPOTENUSE = 2,
    CALC_CIRCLE = 3,
    CALC_RECTANGLE = 4,
    CALC_SQUARE = 5,
    EXIT = 6
} calcOption;

float calculateDistance(float x1, float y1, float x2, float y2);
float calculateHypotenuse(float a, float b);
void calculateCircle(float radius, float* area, float* perimeter);
float calculateSquareArea(float side);
float calculateRectangleArea(float length, float width);

int main() 
{
    int choice = 0;
    do {
        // Display menu
        printf("\nGeometric Calculator Menu:\n");
        printf("1. Calculate distance between two points\n");
        printf("2. Calculate hypotenuse of a right triangle\n");
        printf("3. Calculate area and perimeter of a circle\n");
        printf("4. Calculate area of a square\n");
        printf("5. Calculate area of a rectangle\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch ((calcOption)choice) 
		{
            case CALC_DISTANCE: {
                float x1, y1, x2, y2;
                printf("Enter coordinates of the first point (x1 y1): ");
                scanf("%f %f", &x1, &y1);
                printf("Enter coordinates of the second point (x2 y2): ");
                scanf("%f %f", &x2, &y2);
                float distance = calculateDistance(x1, y1, x2, y2);
                printf("The distance between the points is: %.1f\n", distance);
                break;
            }
            case CALC_HYPOTENUSE: 
			{
                float a, b;
                printf("Enter the lengths of the two legs (a b): ");
                scanf("%f %f", &a, &b);
                float hypotenuse = calculateHypotenuse(a, b);
                printf("The hypotenuse is: %.1f\n", hypotenuse);
                break;
            }
            case CALC_CIRCLE: 
			{
                float radius;
                printf("Enter the radius of the circle: ");
                scanf("%f", &radius);
                float area, perimeter;
                calculateCircle(radius, &area, &perimeter);
                printf("The area of the circle is: %.1f\n", area);
                printf("The perimeter of the circle is: %.1f\n", perimeter);
                break;
            }
            case CALC_SQUARE: 
			{
                float side;
                printf("Enter the side length of the square: ");
                scanf("%f", &side);
                float area = calculateSquareArea(side);
                printf("The area of the square is: %.1f\n", area);
                break;
            }
            case CALC_RECTANGLE: 
			{
                float length, width;
                printf("Enter the length and width of the rectangle: ");
                scanf("%f %f", &length, &width);
                float area = calculateRectangleArea(length, width);
                printf("The area of the rectangle is: %.1f\n", area);
                break;
            }
            case EXIT:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } 
	while (choice != EXIT);
    return 0;
}

float calculateDistance(float x1, float y1, float x2, float y2) 
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

float calculateHypotenuse(float a, float b)
{
    return sqrt(pow(a, 2) + pow(b, 2));
}

void calculateCircle(float radius, float* area, float* perimeter) 
{
    *area = M_PI * pow(radius, 2);
    *perimeter = 2 * M_PI * radius;
}

float calculateSquareArea(float side) 
{
    return pow(side, 2);
}

float calculateRectangleArea(float length, float width) 
{
    return length * width;
}
