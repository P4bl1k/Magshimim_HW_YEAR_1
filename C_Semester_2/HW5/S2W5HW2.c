/*********************************
* Class: MAGSHIMIM C2			 *
* Week 5           				 *
* HW  solution				 	 *
**********************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PRO_OP 1
#define CON_OP 2
#define PRINT_OP 3
#define EXIT_OP 4

#define STR_LEN 50
#define MAX_LIST_LENGTH 10

typedef struct reasonList
{
	char* listName;
	char* reasons[MAX_LIST_LENGTH];
	int numReasons;
} reasonList;


void initList(reasonList* list, char* name);
void addReason(reasonList* list);
void printList(reasonList list);
int menu(void);
void myFgets(char str[], int n);
void deleteList(reasonList list);

int main()
{
	char dillema[STR_LEN] = { 0 };
	int op = 0;

	reasonList proList;
	initList(&proList, "PRO");
	reasonList conList;
	initList(&conList, "CON");

	printf("What is your dillema?\n");
	myFgets(dillema, STR_LEN);

	while (op != EXIT_OP)
	{
		op = menu();

		switch (op)
		{
		case(PRO_OP):
			addReason(&proList);
			break;
		case(CON_OP):
			addReason(&conList);
			break;
		case(PRINT_OP):
			printf("Your dillema:\n");
			printf("%s\n\n", dillema);
			printList(proList);
			printList(conList);
			break;
		case(EXIT_OP):
			deleteList(proList);
			deleteList(conList);
			break;
		}
	}
	printf("Good luck!\n");
	getchar();
	return 0;
}

/*
Function will initialize a reason list
input: the list to init, and its name
output: none
*/
void initList(reasonList* list, char* listName)
{
	list->listName = (char*)malloc(strlen(listName) + 1);
	if (list->listName != NULL)
	{
		strcpy(list->listName, listName);
	}
	list->numReasons = 0;
}

/*
Function will add a reason to the list
input: the list to add to and its name
output: none
*/
void addReason(reasonList* list)
{
	if (list->numReasons >= MAX_LIST_LENGTH)
	{
		printf("Cannot add more reasons to the %s list. It is full.\n", list->listName);
		return;
	}

	char buffer[STR_LEN];
	printf("Enter a reason for %s:\n", list->listName);
	myFgets(buffer, STR_LEN);

	list->reasons[list->numReasons] = (char*)malloc(strlen(buffer) + 1);
	if (list->reasons[list->numReasons] != NULL)
	{
		strcpy(list->reasons[list->numReasons], buffer);
		list->numReasons++;
	}
}
/*
Function will print a list of reasons
input: the list
output: none
*/
void printList(reasonList list)
{
	printf("%s Reasons:\n", list.listName);
	if (list.numReasons == 0)
	{
		printf("No reasons added yet.\n");
	}
	else
	{
		for (int i = 0; i < list.numReasons; i++)
		{
			printf("%d. %s\n", i + 1, list.reasons[i]);
		}
	}
	printf("\n");
}

/*
Function shows menu and returns user's choice
input: none
output: user's choice
*/
int menu()
{
	int op = 0;
	printf("Choose option:\n");
	printf("%d - Add PRO reason\n", PRO_OP);
	printf("%d - Add CON reason\n", CON_OP);
	printf("%d - Print reasons\n", PRINT_OP);
	printf("%d - Exit\n", EXIT_OP);
	scanf("%d", &op);
	while (op < PRO_OP || op > EXIT_OP)
	{
		printf("Invalid option. Try again: ");
		scanf("%d", &op);
	}
	getchar(); // clean buffer
	return op;
}

/*
Function will delete a list
input: the list to delete
output: none
*/
void deleteList(reasonList list)
{
	if (list.listName != NULL)
	{
		free(list.listName);
	}

	for (int i = 0; i < list.numReasons; i++)
	{
		if (list.reasons[i] != NULL)
		{
			free(list.reasons[i]);
		}
	}
}


/*
Function will perform the fgets command and also remove the newline
that might be at the end of the string - a known issue with fgets.
input: the buffer to read into, the number of chars to read
*/
void myFgets(char str[], int n)
{
	fgets(str, n, stdin);
	str[strcspn(str, "\n")] = 0;
}

