#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h> 

#define MAXNAMELEN 20

typedef struct personNode
{
    char name[MAXNAMELEN];
    int age;
    struct personNode* next;
} personNode;


void printMenu();
void printPerson(personNode* head, int* length);
personNode* createPerson(char name[], int age);
void addPerson(personNode** head, int* length);
void insertAtEnd(personNode* head, personNode* newNode);
void removePerson(personNode** head, int* length);
void addVIP(personNode** head, int* length);
void searchInLine(personNode* head,char* name);
void reverseLine(personNode** head);


int main()
{
    int var = 0;
    int counter = 0;
    int* length = &counter;
    personNode* head = NULL;

    while(var != 7)
    {
        printMenu();
        scanf("%d",&var);
        getchar();
        // First Option
        if(var == 1)
        {
            if(head == NULL)
            {
                printf("%d people in line:\n",counter);
            }
            else
            {
                printPerson(head, length);
            }
        }
        // Second Option
        if(var == 2)
        {
            addPerson(&head, length);
        }
        // Third Option
        if(var == 3)
        {
            removePerson(&head, length);
        }
        // Fourth Option
        if(var == 4)
        {
            addVIP(&head, length);
        }
        // Fifth Option
        if(var == 5)
        {
            char name[MAXNAMELEN];
            printf("Enter the name of the person to search:\n");
            fgets(name, sizeof(name), stdin);
            name[strcspn(name, "\n")] = 0; 
            searchInLine(head, name);
        }
        // Sixth Option
        if(var == 6)
        {
            reverseLine(&head);
            printf("Line reversed.\n");
        }
    }
    printf("Goodbye!");
    getchar();
    return 0;
}


/*
Function will print the menu of the MagshiParty
input: none
output: none
*/
void printMenu()
{
    printf("\nWelcome to MagshiParty Line Management Software!\n");
    printf("Please enter your choice from the following options:\n");
    printf("1 - Print line\n");
    printf("2 - Add person to line\n");
    printf("3 - Remove person from line\n");
    printf("4 - VIP guest\n");
    printf("5 - Search in line\n");
    printf("6 - Reverse line\n");
    printf("7 - Exit\n");
}

/*
Function will print a list of people
input: the list (the first person)
output: none
*/
void printPerson(personNode* head, int* length)
{
    printf("%d people in line:\n",*length);
    personNode* curr = head;
    while (curr)
    {
        printf("Name: %s, Age: %d\n", curr->name, curr->age);
        curr = curr->next;
    }
}

/*
Function will create a person
input:name - the name of the person , age - the age of the person
output:
the person updated with correct information
*/
personNode* createPerson(char name[], int age)
{
    personNode* newPerson = (personNode*)malloc(sizeof(personNode));
    strncpy(newPerson->name, name, 20);
    newPerson->age = age;
    newPerson->next = NULL;
    return newPerson;
}

/*
Function to add the guest to the list
input: head - the head of the list
output: none
*/
void addPerson(personNode** head, int* length)
{
    (*length)++;
    char name[MAXNAMELEN];
    int age = 0;
    char friends[3][MAXNAMELEN];
    printf("Enter name:\n");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    printf("Enter age:\n");
    scanf("%d", &age);
    getchar(); // Clear newline

    printf("Enter up to 3 friends' names (press Enter to skip each):\n");
    for (int i = 0; i < 3; i++) 
    {
        printf("Friend %d: ", i + 1);
        fgets(friends[i], sizeof(friends[i]), stdin);
        friends[i][strcspn(friends[i], "\n")] = 0;
    }

    personNode* newPerson = createPerson(name, age);

    // If the list is empty, insert at head
    if (*head == NULL) 
    {
        *head = newPerson;
        return;
    }

    // Search for the closest friend in the line
    personNode* curr = *head;
    personNode* friendNode = NULL;
    personNode* prev = NULL;
    int foundFriend = 0;

    while (curr != NULL)
    {
        for (int i = 0; i < 3; i++) 
        {
            if (strlen(friends[i]) > 0 && strncmp(curr->name, friends[i], MAXNAMELEN) == 0) 
            {
                friendNode = curr;
                foundFriend = 1;
                break;
            }
        }
        if (foundFriend)
            break;
        prev = curr;
        curr = curr->next;
    }

    if (friendNode != NULL) 
    {
        newPerson->next = friendNode->next;
        friendNode->next = newPerson;
    } 
    else 
    {
        curr = *head;
        while (curr->next != NULL) 
        {
            curr = curr->next;
        }
        curr->next = newPerson;
    }
}


/*
Function will add a person to the end of the list
input: head - the head of the list, newNode - the new person to add to the list
output: none
*/
void insertAtEnd(personNode* head, personNode* newNode)
{
    personNode* curr = head;
    while (curr->next) 
    {
        curr = curr->next;
    }
    curr->next = newNode;
}

/*
Function to remove the selected person from the list
input: head - pointer to the head of the list, length - pointer to the number of people
output: none
*/
void removePerson(personNode** head, int* length)
{
    if (*head == NULL) 
    {
        printf("No one in line to remove.\n");
        return;
    }
    char name[MAXNAMELEN] = {0};
    printf("Enter the name of the person to remove:\n");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; 
    
    personNode* curr = *head;
    personNode* prev = NULL;

    while (curr != NULL && strncmp(curr->name, name, MAXNAMELEN) != 0) 
    {
        prev = curr;
        curr = curr->next;
    }

    if (curr == NULL) 
    {
        printf("Person not found in line.\n");
        return;
    }

    if (prev == NULL) 
    {
        *head = curr->next; 
    } 
    else 
    {
        prev->next = curr->next; 
    }
    (*length)--; 
    printf("%s removed from line\n", curr->name);
    free(curr);
}

/*
Function to add a VIP guest at the head of the list
input: head - pointer to the head of the list, length - pointer to the number of people
output: none
*/
void addVIP(personNode** head, int* length)
{
    (*length)++;
    char name[MAXNAMELEN];
    int age = 0;
    printf("VIP GUEST!\n");
    printf("Enter name:\n");
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0;
    printf("Enter age:\n");
    scanf("%d", &age);
    getchar(); 
    personNode* newVIP = createPerson(name, age);
    newVIP->next = *head;
    *head = newVIP;
}

/*
Function to search for a person in the line
input: head - pointer to the head of the list, name - the name of the person to search for
output: none
*/
void searchInLine(personNode* head,char* name)
{
    personNode* curr = head;
    while (curr != NULL) 
    {
        if (strncmp(curr->name, name, MAXNAMELEN) == 0) 
        {
            printf("%s found in line\n", curr->name);
            return;
        }
        curr = curr->next;
    }
    printf("%s not found in line.\n", name);
}

/*
Function to reverse the order of the line
input: head - pointer to the head of the list
output: none
*/
void reverseLine(personNode** head)
{
    personNode* prev = NULL;
    personNode* curr = *head;
    personNode* next = NULL;

    while (curr != NULL) 
    {
        next = curr->next; 
        curr->next = prev; 
        prev = curr; 
        curr = next; 
    }
    *head = prev; 
}