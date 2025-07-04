#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct personNode
{
    char name[20];
    int age;
    struct personNode* next;
} personNode;

void insertAtEnd(personNode* head, personNode* newNode);
personNode* createPerson(char name[], int age);
void PrintPerson(personNode* head);
personNode* copyList(personNode* head);
void freeList(personNode* head);
int listLength(personNode* head, int* length);

int main()
{
    int peopleInList = 0;
    int counter = 0;
    int* length = &counter;
    personNode* head = NULL;
    personNode* copy = NULL;
    printf("How many people in the list? ");
    scanf("%d", &peopleInList);
    getchar();
    while (peopleInList > 0)
    {
        char name[20];
        int age;
        printf("Enter name: ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0; 
        printf("Enter age: ");
        scanf("%d", &age);
        getchar();
        personNode* newPerson = createPerson(name, age);
        if (head == NULL)
        {
            head = newPerson;
        }
        else
        {
            insertAtEnd(head, newPerson);
        }
        peopleInList--;
    }
    printf("\n");
    printf("People List\n");
    PrintPerson(head);
    listLength(head,length);
    printf("The length of the list is: %d\n\n",counter);
    copy = copyList(head);
    printf("New list:\n");
    PrintPerson(copy);
    freeList(head);
    freeList(copy);
    getchar();
    return 0;
}

/*
Function will create a person
input:
name - the name of the person
age - the age of the person
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
Function will add a song to the playlist
input: 
firstNode - the first node of the playlist
newNode - the new song to add to the playlist
output:
none
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
Function will print a list of people
input: the list (the first person)
output:
none
*/
void PrintPerson(personNode* head)
{
    personNode* curr = head;
    while (curr)
    {
        printf("Name: %s || Age: %d\n", curr->name, curr->age);
        curr = curr->next;
    }
    printf("\n");
}
/*
Function will return the length of the list
input: the first node of the list
output: the length of the list
*/
int listLength(personNode* head, int* length)
{
    if (head == NULL)
    { 
        return *length;
    }
    (*length)++;
    return listLength(head->next, length);
}

/*
Function will create a copy of the list
input: the first node of the list
output: a new list with the same elements
*/
personNode* copyList(personNode* head)
{
    if (head == NULL)
    {
        return NULL;
    }
    personNode* newHead = createPerson(head->name, head->age);
    personNode* currOriginal = head->next;
    personNode* currNew = newHead;

    while (currOriginal) 
    {
        currNew->next = createPerson(currOriginal->name, currOriginal->age);
        currOriginal = currOriginal->next;
        currNew = currNew->next;
    }
    return newHead;
}

/*
Function will free the memory allocated for the list
input:
head - the first node of the list
output:
none
*/
void freeList(personNode* head)
{
    personNode* curr = head;
    while (curr)
    {
        personNode* temp = curr;
        curr = curr->next;
        free(temp);
    }
}