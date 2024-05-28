#include <stdio.h>
#include <stdlib.h>

#define MAX 10 // Maximum size of the array

typedef struct {
    int arr[MAX];
    int front1, rear1;
    int front2, rear2;
} TwoQueue;

void initializeQueue(TwoQueue* q) {
    q->front1 = -1;
    q->rear1 = -1;
    q->front2 = MAX;
    q->rear2 = MAX;
}

int isFull(TwoQueue* q) {
    return q->rear1 + 1 == q->rear2;
}

int isEmpty1(TwoQueue* q) {
    return q->front1 == -1;
}

int isEmpty2(TwoQueue* q) {
    return q->front2 == MAX;
}

void addq(TwoQueue* q, int queueNumber, int value) {
    if (isFull(q)) {
        printf("Queue Overflow\n");
        return;
    }
    if (queueNumber == 1) {
        if (q->rear1 == -1) {
            q->front1 = q->rear1 = 0;
        } else {
            q->rear1++;
        }
        q->arr[q->rear1] = value;
    } else if (queueNumber == 2) {
        if (q->rear2 == MAX) {
            q->front2 = q->rear2 = MAX - 1;
        } else {
            q->rear2--;
        }
        q->arr[q->rear2] = value;
    }
}

void delq(TwoQueue* q, int queueNumber) {
    if (queueNumber == 1) {
        if (isEmpty1(q)) {
            printf("Queue Underflow\n");
            return;
        }
        printf("Deleted from Queue 1: %d\n", q->arr[q->front1]);
        if (q->front1 == q->rear1) {
            q->front1 = q->rear1 = -1;
        } else {
            q->front1++;
        }
    } else if (queueNumber == 2) {
        if (isEmpty2(q)) {
            printf("Queue Underflow\n");
            return;
        }
        printf("Deleted from Queue 2: %d\n", q->arr[q->front2]);
        if (q->front2 == q->rear2) {
            q->front2 = q->rear2 = MAX;
        } else {
            q->front2--;
        }
    }
}

void displayQueue(TwoQueue* q, int queueNumber) {
    if (queueNumber == 1) {
        if (isEmpty1(q)) {
            printf("Queue 1 is empty\n");
            return;
        }
        printf("Queue 1: ");
        for (int i = q->front1; i <= q->rear1; i++) {
            printf("%d ", q->arr[i]);
        }
        printf("\n");
    } else if (queueNumber == 2) {
        if (isEmpty2(q)) {
            printf("Queue 2 is empty\n");
            return;
        }
        printf("Queue 2: ");
        for (int i = q->front2; i >= q->rear2; i--) {
            printf("%d ", q->arr[i]);
        }
        printf("\n");
    }
}

int main() {
    TwoQueue q;
    initializeQueue(&q);

    // Test operations
    addq(&q, 1, 10);
    addq(&q, 1, 20);
    addq(&q, 2, 30);
    addq(&q, 2, 40);

    displayQueue(&q, 1); // Displays Queue 1
    displayQueue(&q, 2); // Displays Queue 2

    delq(&q, 1); // Deletes from Queue 1
    delq(&q, 2); // Deletes from Queue 2

    displayQueue(&q, 1); // Displays Queue 1
    displayQueue(&q, 2); // Displays Queue 2

    return 0;
}
