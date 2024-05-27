#include <stdio.h>
#include <stdlib.h>

// Define a structure for a node in the doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Define a structure for the doubly linked list based Queue
struct Queue {
    struct Node* front;
    struct Node* rear;
};

// Function to create a new node
struct Node* createNode(int data) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}

// Function to check if the queue is empty
int isEmpty(struct Queue* queue) {
    return (queue->front == NULL);
}

// Function to add an item to the queue (enqueue)
void enqueue(struct Queue* queue, int data) {
    struct Node* newNode = createNode(data);
    if (isEmpty(queue)) {
        queue->front = newNode;
        queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        newNode->prev = queue->rear;
        queue->rear = newNode;
    }
}
// Function to remove an item from the queue (dequeue)
int dequeue(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return -1;
    }
    int data = queue->front->data;
    struct Node* temp = queue->front;
    queue->front = queue->front->next;
    if (queue->front != NULL)
        queue->front->prev = NULL;
    free(temp);
    return data;
}

// Function to display the elements of the queue
void display(struct Queue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }
    struct Node* temp = queue->front;
    printf("Queue elements: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Driver program
int main() {
    struct Queue* queue = createQueue();

    enqueue(queue, 10);
    enqueue(queue, 20);
    enqueue(queue, 30);

    printf("After Enqueue:\n");
    display(queue);

    dequeue(queue);
    dequeue(queue);

    printf("After Dequeue:\n");
    display(queue);

    return 0;
}
