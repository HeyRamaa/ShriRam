#include <stdio.h>
#include <stdlib.h>

// Doubly linked list node
struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to insert a node at the end of the list
void insertEnd(struct Node** head, int data) {
    struct Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    struct Node* last = *head;
    while (last->next != NULL)
        last = last->next;
    last->next = newNode;
    newNode->prev = last;
}

// Function to merge two sorted doubly linked lists
struct Node* mergeLists(struct Node* head1, struct Node* head2) {
    struct Node* mergedHead = NULL;
    struct Node* temp = NULL;

    while (head1 != NULL && head2 != NULL) {
        if (head1->data < head2->data) {
            if (mergedHead == NULL) {
                mergedHead = head1;
                temp = mergedHead;
            } else {
                temp->next = head1;
                head1->prev = temp;
                temp = temp->next;
            }
            head1 = head1->next;
        } else {
            if (mergedHead == NULL) {
                mergedHead = head2;
                temp = mergedHead;
            } else {
                temp->next = head2;
                head2->prev = temp;
                temp = temp->next;
            }
            head2 = head2->next;
        }
    }

    if (head1 != NULL)
        temp->next = head1;
    else if (head2 != NULL)
        temp->next = head2;

    return mergedHead;
}

// Function to display the merged list
void displayList(struct Node* head) {
    while (head != NULL) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}
// Driver code
int main() {
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;
    
    // Inserting elements into the first list
    insertEnd(&head1, 1);
    insertEnd(&head1, 3);
    insertEnd(&head1, 5);
    
    // Inserting elements into the second list
    insertEnd(&head2, 2);
    insertEnd(&head2, 4);
    insertEnd(&head2, 6);

    printf("First sorted list: ");
    displayList(head1);
    printf("Second sorted list: ");
    displayList(head2);
    
    // Merging the two sorted lists
    struct Node* mergedList = mergeLists(head1, head2);
    printf("Merged sorted list: ");
    displayList(mergedList);

    return 0;
}

