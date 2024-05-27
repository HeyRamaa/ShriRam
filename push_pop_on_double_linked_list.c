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

// Function to push a node onto the stack
void push(struct Node** top, int data) {
    struct Node* newNode = createNode(data);
    if (*top == NULL) {
        *top = newNode;
        return;
    }
    (*top)->next = newNode;
    newNode->prev = *top;
    *top = newNode;
}

// Function to pop a node from the stack
int pop(struct Node** top) {
    if (*top == NULL) {
        printf("Stack underflow!\n");
        return -1; // Stack underflow condition
    }
    struct Node* temp = *top;
    int poppedData = temp->data;
    *top = (*top)->prev;
    if (*top != NULL) {
        (*top)->next = NULL;
    }
    free(temp);
    return poppedData;
}

// Function to display the elements of the stack
void displayStack(struct Node* top) {
    printf("Stack: ");
    while (top != NULL) {
        printf("%d ", top->data);
        top = top->prev;
    }
    printf("\n");
}
// Driver code
int main() {
    struct Node* top = NULL;

    // Pushing elements onto the stack
    push(&top, 1);
    push(&top, 2);
    push(&top, 3);

    // Displaying the stack
    displayStack(top);

    // Popping elements from the stack
    printf("Popped element: %d\n", pop(&top));
    printf("Popped element: %d\n", pop(&top));

    // Displaying the stack after popping
    displayStack(top);
    return 0;
}
