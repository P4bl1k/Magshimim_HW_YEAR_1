#include <stdio.h>
#include <stdlib.h>

typedef struct Node 
{
    int data;
    struct Node* next;
} Node;

/*
function concatenate(list1, list2) concatenates two linked lists.
input: list1 - a pointer to the first node of the first linked list
       list2 - a pointer to the first node of the second linked list
output: returns a pointer to the first node of the concatenated linked list
runtime: O(min(n1,n2) + O(1), where n1 is the length of list1 and n2 is the length of list2.
*/
Node* concatenate(Node* list1, Node* list2) 
{
    if (!list1) 
    {
        return list2;
    }
    if (!list2) 
    {
        return list1;
    }
    Node* curr = list1;
    while (curr->next) 
    {
        curr = curr->next;
    }
    curr->next = list2;
    return list1;
}

int main() 
{
    // Example usage
    // Creating two linked lists: 1 -> 2 -> 3 and 4 -> 5
    Node* a = malloc(sizeof(Node)); a->data = 1;
    Node* b = malloc(sizeof(Node)); b->data = 2;
    Node* c = malloc(sizeof(Node)); c->data = 3;
    a->next = b; 
    b->next = c; 
    c->next = NULL;

    Node* d = malloc(sizeof(Node)); d->data = 4;
    Node* e = malloc(sizeof(Node)); e->data = 5;
    d->next = e; e->next = NULL;

    Node* result = concatenate(a, d);
    return 0;
}