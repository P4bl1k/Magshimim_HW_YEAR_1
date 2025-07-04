#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node* next;
} Node;

Node* rotate_left(Node* head, int k);
Node* create_node(int data);
void printList(Node* head); 
void free_list(Node* head);
int main() 
{
    int n= 0;
    int k = 0;
    int val = 0;
    Node *head = NULL;
    Node *tail = NULL;

    printf("How many nodes in list? ");
    scanf("%d", &n);
    getchar();
    for (int i = 0; i < n; i++) 
    {
        printf("Enter number: ");
        scanf("%d", &val);
        Node* new_node = create_node(val);
        if (!head) {
            head = new_node;
            tail = new_node;
        } else {
            tail->next = new_node;
            tail = new_node;
        }
    }

    printf("Choose a number k, and the list will be rotated k places to the left: ");
    scanf("%d", &k);
    getchar();
    head = rotate_left(head, k);

    printf("The rotated list:\n");
    printList(head);
    getchar();
    free_list(head);
    return 0;
}

/*
function to rotate the linked list to the left by k nodes,where k is the number of nodes to rotate
input: head of the linked list and k
output: new head of the linked list after rotation
runtime: O(n), where n is the number of nodes in the linked list
*/
Node* rotate_left(Node* head, int k) 
{
    if (!head || k == 0) 
    {
        return head;
    }
    Node* curr = head;
    int length = 1;
    while (curr->next) 
    {
        curr = curr->next;
        length++;
    }

    k = k % length;
    if (k == 0) 
    {
        return head;
    }
    Node* tail = curr;
    Node* new_tail = head;
    for (int i = 1; i < k; i++) 
    {
        new_tail = new_tail->next;
    }

    Node* new_head = new_tail->next;

    new_tail->next = NULL;
    tail->next = head;

    return new_head;
}
Node* create_node(int data)
{
    Node* node = malloc(sizeof(Node));
    if (!node) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    node->data = data;
    node->next = NULL;
    return node;
}
/*
function to print the linked list
input: head of the linked list
output: prints the linked list in a readable format
runtime: O(n)
*/
void printList(Node* head)
{
    while (head) {
        printf("%d -> ", head->data);
        head = head->next;
    }
    printf("NULL\n");
}
void free_list(Node* head) 
{
    while (head) 
    {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}