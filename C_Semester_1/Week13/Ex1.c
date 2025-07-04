#include <stdio.h>

#define ROWS 5
#define SEATS_IN_ROW 3

#define CHEAP_TICKET_PRICE 25
#define NORMAL_TICKET_PRICE 35
#define VIP_TICKET_PRICE 50

void printCinema(int cinema[][SEATS_IN_ROW], int rows);
int buyTicket(int cinema[][SEATS_IN_ROW], int row, int seat);
int countOccupiedSeats(int cinema[][SEATS_IN_ROW]);
int selectCheapestSeat(int cinema[][SEATS_IN_ROW]);
void applyDiscount(int cinema[][SEATS_IN_ROW], int discount);
void showMenu();

int main(void)
{
    int cinema[ROWS][SEATS_IN_ROW] = {
        {CHEAP_TICKET_PRICE, CHEAP_TICKET_PRICE, CHEAP_TICKET_PRICE},
        {NORMAL_TICKET_PRICE, NORMAL_TICKET_PRICE, NORMAL_TICKET_PRICE},
        {NORMAL_TICKET_PRICE, VIP_TICKET_PRICE, NORMAL_TICKET_PRICE},
        {NORMAL_TICKET_PRICE, NORMAL_TICKET_PRICE, NORMAL_TICKET_PRICE},
        {CHEAP_TICKET_PRICE, CHEAP_TICKET_PRICE, CHEAP_TICKET_PRICE}
    };
    
    int choice, row, seat, discount;
    do {
        showMenu();
        scanf("%d", &choice);
        switch (choice) 
		{
            case 1:
                printCinema(cinema, ROWS);
                break;
            case 2:
                printf("Enter row (0-4) and seat (0-2): ");
                scanf("%d %d", &row, &seat);
                if (buyTicket(cinema, row, seat))
				{
                    printf("Purchase successful!\n");
                } 
				else 
				{
                    printf("Seat is already taken.\n");
                }
                break;
            case 3:
                printf("Total occupied seats: %d\n", countOccupiedSeats(cinema));
                break;
            case 4:
                selectCheapestSeat(cinema);
                break;
            case 5:
                printf("Enter discount amount: ");
                scanf("%d", &discount);
                applyDiscount(cinema, discount);
                printf("Discount applied!\n");
                break;
            case 6:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice, please enter a number between 1 and 6.\n");
        }
    }
	while (choice != 6);
    
    return 0;
}
/*
Function to Print The Seats
input: Seats and Rows
output: The Printed Cinema
*/
void printCinema(int mat[][SEATS_IN_ROW], int rows) 
{
	int row = 0;
	int col = 0;
    for (row = 0; row < rows; row++) 
	{
        for (col = 0; col < SEATS_IN_ROW; col++) 
		{
            printf("%d ", mat[row][col]);
        }
        printf("\n");
    }
}
/*
Function to buy a ticket
input: Seats and Rows and cinema itself
output: 0 or 1
*/
int buyTicket(int cinema[][SEATS_IN_ROW], int row, int seat) 
{
    if (cinema[row][seat] == -1) 
	{
        return 0;
    }
    cinema[row][seat] = -1;
    return 1;
}
/*
Function to Count the Amount of Occupied Seats
input: The Cinema Itself
output: The Amount of Occupied Seats
*/
int countOccupiedSeats(int cinema[][SEATS_IN_ROW]) 
{
	int col = 0;
	int row = 0;
    int count = 0;
    for (row = 0; row < ROWS; row++) 
	{
        for (col = 0; col < SEATS_IN_ROW; col++) 
		{
            if (cinema[row][col] == -1) 
			{
                count++;
            }
        }
    }
    return count;
}
/*
Function to Select the cheapest seat in the array
input: Cinema itself
output: The Cheapest Seat
*/
int selectCheapestSeat(int cinema[][SEATS_IN_ROW]) 
{
    int minPrice = 1000;
    int rowIdx = -1, colIdx = -1;
    int col = 0;
	int row = 0;
    for (row = 0; row < ROWS; row++) 
	{
        for (col = 0; col < SEATS_IN_ROW; col++) 
		{
            if (cinema[row][col] != -1 && cinema[row][col] < minPrice) 
			{
                minPrice = cinema[row][col];
                rowIdx = row;
                colIdx = col;
            }
        }
    }
    
    if (rowIdx != -1) 
	{
        printf("Cheapest seat available at row %d, seat %d for price %d\n", rowIdx, colIdx, minPrice);
        return minPrice;
    }
    printf("No available seats!\n");
    return -1;
}
/*
Function to Apply Some Amount Of Discount To the Seats
input: Cinema Itself and discount amount
output: none
*/
void applyDiscount(int cinema[][SEATS_IN_ROW], int discount) 
{
	int col = 0;
	int row = 0;
    for (row = 0; row < ROWS; row++)
	{
        for (col = 0; col < SEATS_IN_ROW; col++) 
		{
            if (cinema[row][col] != -1) 
			{
                cinema[row][col] -= discount;
                if (cinema[row][col] < 0) 
				{
                    cinema[row][col] = 0;
                }
            }
        }
    }
}
/*
Function to Show The Cinema Ticket System
input: none
output: none
*/
void showMenu() 
{
    printf("\nCinema Ticket System\n");
    printf("1. Print cinema hall\n");
    printf("2. Buy a ticket\n");
    printf("3. Count occupied seats\n");
    printf("4. Show cheapest available seat\n");
    printf("5. Apply discount to available seats\n");
    printf("6. Exit\n");
    printf("Enter your choice: ");
}
