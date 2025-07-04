#include <stdio.h>
#include <math.h>

void calculateDistance();
void calculateHypotenuse();
void calculateCircleAreaAndPerimeter();
void calculateSquareArea();
void calculateRectangleArea();

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

        // Perform the selected operation
        switch (choice) {
            case 1:
                calculateDistance();
                break;
            case 2:
                calculateHypotenuse();
                break;
            case 3:
                calculateCircleAreaAndPerimeter();
                break;
            case 4:
                calculateSquareArea();
                break;
            case 5:
                calculateRectangleArea();
                break;
            case 6:
                printf("Exiting the program. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please select a valid option.\n");
        }
    } 
	while (choice != 6);

    return 0;
}
// Functions

/*
Function to calculate the distance between two points
input: two points in a graph
output: none
*/
void calculateDistance() {
    float x1 = 0, y1 = 0, x2 = 0, y2 = 0, distance = 0;

    printf("Enter coordinates of the first point (x1 y1): ");
    scanf("%f %f", &x1, &y1);
    printf("Enter coordinates of the second point (x2 y2): ");
    scanf("%f %f", &x2, &y2);

    distance = sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
    printf("The distance between the points is: %.1f\n", distance);
}
/*
Function to calculate the hypotenuse of a right triangle
input: two lines that crrates a hypotenuse
output: none
*/

void calculateHypotenuse() {
    float a = 0, b = 0, hypotenuse = 0;

    printf("Enter the lengths of the two legs (a b): ");
    scanf("%f %f", &a, &b);

    hypotenuse = sqrt(pow(a, 2) + pow(b, 2));
    printf("The hypotenuse is: %.1f\n", hypotenuse);
}
/*
Function to calculate the area and perimeter of a circle
input: the radius of circle
output: none
*/

void calculateCircleAreaAndPerimeter() {
    float radius = 0, area = 0, perimeter = 0;

    printf("Enter the radius of the circle: ");
    scanf("%f", &radius);

    area = M_PI * pow(radius, 2);
    perimeter = 2 * M_PI * radius;
    printf("The area of the circle is: %.1f\n", area);
    printf("The perimeter of the circle is: %.1f\n", perimeter);
}
/*
// Function to calculate the area of a square
input: side length of a square
output: none
*/
void calculateSquareArea() {
    float side = 0, area = 0;

    printf("Enter the side length of the square: ");
    scanf("%f", &side);

    area = pow(side, 2);
    printf("The area of the square is: %.1f\n", area);
}
/*
// Function to calculate the area of a rectangle
input: length and width of rectangle
output: none
*/
void calculateRectangleArea() {
    float length = 0, width = 0, area = 0;

    printf("Enter the length and width of the rectangle: ");
    scanf("%f %f", &length, &width);

    area = length * width;
    printf("The area of the rectangle is: %.1f\n", area);
}
