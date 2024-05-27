#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
struct Deque {
    int data[MAX_SIZE];
    int front, rear;
};

void initializeDeque(struct Deque *deque) {
    deque->front = -1;
    deque->rear = -1;
}
int isFull(struct Deque *deque) {
    return ((deque->front == 0 && deque->rear == MAX_SIZE - 1) || (deque->front == deque->rear + 1));
}
int isEmpty(struct Deque *deque) {
    return (deque->front == -1);
}
void insertFront(struct Deque *deque, int value) {
    if (isFull(deque)) {
        printf("Deque Overflow\n");
        return;
    }
    if (deque->front == -1) {
        deque->front = 0;
        deque->rear = 0;
    } else if (deque->front == 0)
        deque->front = MAX_SIZE - 1;
    else
        deque->front = deque->front - 1;
    deque->data[deque->front] = value;
}
void insertRear(struct Deque *deque, int value) {
    if (isFull(deque)) {
        printf("Deque Overflow\n");
        return;
    }
    if (deque->front == -1) {
        deque->front = 0;
        deque->rear = 0;
    } else if (deque->rear == MAX_SIZE - 1)
        deque->rear = 0;
    else
        deque->rear = deque->rear + 1;
    deque->data[deque->rear] = value;
}
int deleteFront(struct Deque *deque) {
    if (isEmpty(deque)) {
        printf("Deque Underflow\n");
        return -1;
    }
    int value = deque->data[deque->front];
    if (deque->front == deque->rear) {
        deque->front = -1;
        deque->rear = -1;
    } else if (deque->front == MAX_SIZE - 1)
        deque->front = 0;
    else
        deque->front = deque->front + 1;
    return value;
}
int deleteRear(struct Deque *deque) {
    if (isEmpty(deque)) {
        printf("Deque Underflow\n");
        return -1;
    }
    int value = deque->data[deque->rear];
    if (deque->front == deque->rear) {
        deque->front = -1;
        deque->rear = -1;
    } else if (deque->rear == 0)
        deque->rear = MAX_SIZE - 1;
    else
        deque->rear = deque->rear - 1;
    return value;
}
void display(struct Deque *deque) {
    if (isEmpty(deque)) {
        printf("Deque is empty\n");
        return;
    }
    int i;
    printf("Deque elements: ");
    if (deque->front <= deque->rear) {
        for (i = deque->front; i <= deque->rear; i++)
            printf("%d ", deque->data[i]);
    } else {
        for (i = deque->front; i < MAX_SIZE; i++)
            printf("%d ", deque->data[i]);
        for (i = 0; i <= deque->rear; i++)
            printf("%d ", deque->data[i]);
    }
    printf("\n");
}
int main() {
    struct Deque deque;
    initializeDeque(&deque);

    insertRear(&deque, 5);
    insertRear(&deque, 10);
    insertFront(&deque, 15);
    insertFront(&deque, 20);

    display(&deque);

    printf("Deleted element from rear: %d\n", deleteRear(&deque));
    printf("Deleted element from front: %d\n", deleteFront(&deque));

    display(&deque);

    insertFront(&deque, 25);
    insertRear(&deque, 30);

    display(&deque);

    return 0;
}

