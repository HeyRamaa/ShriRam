#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 100

// Structure to represent a stack
struct Stack {
    int top;
    char items[MAX_SIZE];
};
// Function to initialize the stack
void initializeStack(struct Stack *stack) {
    stack->top = -1;
}
// Function to check if the stack is empty
int isEmpty(struct Stack *stack) {
    return stack->top == -1;
}
// Function to push an element onto the stack
void push(struct Stack *stack, char c) {
    if (stack->top == MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    stack->items[++stack->top] = c;
}
// Function to pop an element from the stack
char pop(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack->items[stack->top--];
}
// Function to return the top element of the stack without removing it
char peek(struct Stack *stack) {
    if (isEmpty(stack)) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack->items[stack->top];
}
// Function to determine if a character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}
// Function to determine the precedence of an operator
int precedence(char c) {
    if (c == '+' || c == '-')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else
        return 0;
}
// Function to convert infix expression to prefix expression
void infixToPrefix(char *infix, char *prefix) {
    struct Stack stack;
    initializeStack(&stack);
    int i, j;
    j = 0;

    // Reverse the infix expression
    int len = strlen(infix);
    for (i = len - 1; i >= 0; i--) {
        if (infix[i] == '(')
            infix[i] = ')';
        else if (infix[i] == ')')
            infix[i] = '(';
    }
    // Prefix expression conversion
    for (i = 0; infix[i] != '\0'; i++) {
        if (isalnum(infix[i])) {
            prefix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(&stack, infix[i]);
        } else if (infix[i] == ')') {
            while (peek(&stack) != '(') {
                prefix[j++] = pop(&stack);
            }
            pop(&stack); // Discard the '('
        } else if (isOperator(infix[i])) {
            while (!isEmpty(&stack) && precedence(infix[i]) <= precedence(peek(&stack))) {
                prefix[j++] = pop(&stack);
            }
            push(&stack, infix[i]);
        }
    }
    // Pop remaining operators from the stack
    while (!isEmpty(&stack)) {
        prefix[j++] = pop(&stack);
    }
    prefix[j] = '\0';
    // Reverse the prefix expression to get the final result
    len = strlen(prefix);
    for (i = 0; i < len / 2; i++) {
        char temp = prefix[i];
        prefix[i] = prefix[len - i - 1];
        prefix[len - i - 1] = temp;
    }
}
// Function to evaluate a prefix expression
int evaluatePrefix(char *prefix) {
    struct Stack stack;
    initializeStack(&stack);
    int i, operand1, operand2, result;

    for (i = 0; prefix[i] != '\0'; i++) {
        if (isdigit(prefix[i])) {
            push(&stack, prefix[i] - '0');
        } else if (isOperator(prefix[i])) {
            operand2 = pop(&stack);
            operand1 = pop(&stack);
            switch (prefix[i]) {
                case '+': result = operand1 + operand2; break;
                case '-': result = operand1 - operand2; break;
                case '*': result = operand1 * operand2; break;
                case '/': result = operand1 / operand2; break;
            }
            push(&stack, result);
        }
    }
    return pop(&stack);
}
