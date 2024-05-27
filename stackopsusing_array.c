#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100
struct TwoStacks {
    int top1;
    int top2;
    int items[MAX_SIZE];
};
// Function to initialize the two stacks
void initializeTwoStacks(struct TwoStacks *stacks) {
    stacks->top1 = -1;
    stacks->top2 = MAX_SIZE;
}
// Function to check if the first stack is full
int isFull1(struct TwoStacks *stacks) {
    return (stacks->top1 == stacks->top2 - 1);
}
// Function to check if the second stack is full
int isFull2(struct TwoStacks *stacks) {
    return (stacks->top2 == stacks->top1 + 1);
}
// Function to check if the first stack is empty
int isEmpty1(struct TwoStacks *stacks) {
    return (stacks->top1 == -1);
}
// Function to check if the second stack is empty
int isEmpty2(struct TwoStacks *stacks) {
    return (stacks->top2 == MAX_SIZE);
}
// Function to push an element onto the first stack
void push1(struct TwoStacks *stacks, int value) {
    if (isFull1(stacks)) {
        printf("Stack 1 Overflow\n");
        return;
    }
    stacks->items[++stacks->top1] = value;
}
// Function to push an element onto the second stack
void push2(struct TwoStacks *stacks, int value) {
    if (isFull2(stacks)) {
        printf("Stack 2 Overflow\n");
        return;
    }
    stacks->items[--stacks->top2] = value;
}
// Function to pop an element from the first stack
int pop1(struct TwoStacks *stacks) {
    if (isEmpty1(stacks)) {
        printf("Stack 1 Underflow\n");
        exit(1);
    }
    return stacks->items[stacks->top1--];
}
// Function to pop an element from the second stack
int pop2(struct TwoStacks *stacks) {
    if (isEmpty2(stacks)) {
        printf("Stack 2 Underflow\n");
        exit(1);
    }
    return stacks->items[stacks->top2++];
}
// Function to display the contents of the first stack
void displayStack1(struct TwoStacks *stacks) {
    printf("Stack 1: ");
    for (int i = stacks->top1; i >= 0; i--) {
        printf("%d ", stacks->items[i]);
    }
    printf("\n");
}
// Function to display the contents of the second stack
void displayStack2(struct TwoStacks *stacks) {
    printf("Stack 2: ");
    for (int i = stacks->top2; i < MAX_SIZE; i++) {
        printf("%d ", stacks->items[i]);
    }
    printf("\n");
}
// Function to display both stacks
void displayStacks(struct TwoStacks *stacks) {
    displayStack1(stacks);
    displayStack2(stacks);
}
int main() {
    struct TwoStacks stacks;
    initializeTwoStacks(&stacks);

    push1(&stacks, 1);
    push1(&stacks, 2);
    push1(&stacks, 3);

    push2(&stacks, 4);
    push2(&stacks, 5);
    push2(&stacks, 6);

    displayStacks(&stacks);

    printf("Popped element from Stack 1: %d\n", pop1(&stacks));
    printf("Popped element from Stack 2: %d\n", pop2(&stacks));

    displayStacks(&stacks);

    return 0;
}
