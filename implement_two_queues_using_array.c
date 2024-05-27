#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define MAX_QUEUES 5

struct Queue {
    int data[MAX_SIZE];
    int front[MAX_QUEUES];
    int rear[MAX_QUEUES];
};

void initializeQueue(struct Queue *queue, int queue_num) {
    queue->front[queue_num] = -1;
    queue->rear[queue_num] = -1;
}

int isFull(struct Queue *queue, int queue_num) {
    return (queue->rear[queue_num] == MAX_SIZE - 1);
}

int isEmpty(struct Queue *queue, int queue_num) {
    return (queue->front[queue_num] == -1 || queue->front[queue_num] > queue->rear[queue_num]);
}

void addq(struct Queue *queue, int queue_num, int value) {
    if (isFull(queue, queue_num)) {
        printf("Queue %d Overflow\n", queue_num);
        return;
    }
    if (isEmpty(queue, queue_num)) {
        queue->front[queue_num] = 0;
        queue->rear[queue_num] = 0;
    } else {
        queue->rear[queue_num]++;
    }
    queue->data[queue->rear[queue_num]] = value;
}
int delq(struct Queue *queue, int queue_num) {
    if (isEmpty(queue, queue_num)) {
        printf("Queue %d Underflow\n", queue_num);
        return -1;
    }
    int value = queue->data[queue->front[queue_num]];
    if (queue->front[queue_num] == queue->rear[queue_num]) {
        queue->front[queue_num] = -1;
        queue->rear[queue_num] = -1;
    } else {
        queue->front[queue_num]++;
    }
    return value;
}
void display(struct Queue *queue, int queue_num) {
    if (isEmpty(queue, queue_num)) {
        printf("Queue %d is empty\n", queue_num);
        return;
    }
    printf("Queue %d elements: ", queue_num);
    for (int i = queue->front[queue_num]; i <= queue->rear[queue_num]; i++) {
        printf("%d ", queue->data[i]);
    }
    printf("\n");
}

int main() {
    struct Queue queue;
    for (int i = 0; i < MAX_QUEUES; i++) {
        initializeQueue(&queue, i);
    }

    addq(&queue, 0, 5);
    addq(&queue, 0, 10);
    addq(&queue, 1, 15);
    addq(&queue, 1, 20);
    addq(&queue, 2, 25);
    addq(&queue, 2, 30);

    display(&queue, 0);
    display(&queue, 1);
    display(&queue, 2);

    printf("Deleted element from Queue 1: %d\n", delq(&queue, 1));

    display(&queue, 1);

    return 0;
}
