#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

Node* create_node(int data);
Node* find_kth_from_end(Node* head, int k);
void print_from_node(Node* node);
void free_list(Node* head);

int main() 
{
    int n = 0;
    int k = 0;
    int value = 0;
    Node *head = NULL;
    Node *tail = NULL;

    printf("How many nodes in list? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++) 
    {
        printf("Enter number: ");
        scanf("%d", &value);
        Node* new_node = create_node(value);

        if (!head) 
        {
            head = new_node;
            tail = new_node;
        }
        else 
        {
            tail->next = new_node;
            tail = new_node;
        }
    }

    printf("Choose a number k, and the k last values will be printed:\n");
    scanf("%d", &k);
    getchar();
    Node* start = find_kth_from_end(head, k);
    printf("The list from that node to the end:\n");
    print_from_node(start);
    getchar();
    free_list(head);
    return 0;
}

// function to create a new node
// input: data - the value to be stored in the node
// output: returns a pointer to the newly created node
// runtime: O(1)
Node* create_node(int data)
{
    Node* node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// function to find the k-th node from the end of the list
// input: head - pointer to the head of the linked list 
//        k - the position from the end (1-based index)
// output: returns a pointer to the k-th node from the end, or NULL if k is out of bounds
// runtime: O(n), where n is the length of the linked list
Node* find_kth_from_end(Node* head, int k) 
{
    Node* fast = head;
    Node* slow = head;

    for (int i = 0; i < k; i++) {
        if (fast == NULL) return NULL;
        fast = fast->next;
    }

    while (fast) {
        fast = fast->next;
        slow = slow->next;
    }

    return slow;
}

// function to print the values from a given node to the end of the list
// input: node - pointer to the starting node   
// output: prints the values from the node to the end of the list
// runtime: O(m), where m is the number of nodes from the given node to the end of the list
void print_from_node(Node* node) 
{
    while (node) {
        printf("%d ", node->data);
        node = node->next;
    }
    printf("\n");
}
// function to free the linked list
// input: head - pointer to the head of the linked list
// output: frees all nodes in the linked list
// runtime: O(n), where n is the length of the linked list
void free_list(Node* head) 
{
    while (head) 
    {
        Node* temp = head;
        head = head->next;
        free(temp);
    }
}