#include<stdio.h>
#include<stdlib.h>
#define MAX_STACK_SIZE 100

// Define structure for tree node
struct TreeNode {
    int data;
    struct TreeNode* left;
    struct TreeNode* right;
};

// Define structure for stack
struct Stack {
    int top;
    struct TreeNode* array[MAX_STACK_SIZE];
};

// Create a new stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

// Check if stack is empty
int isEmpty(struct Stack* stack) {
    return (stack->top == -1);
}

// Push an item to stack
void push(struct Stack* stack, struct TreeNode* item) {
    if (stack->top >= MAX_STACK_SIZE - 1)
        return;
    stack->array[++stack->top] = item;
}

// Pop an item from stack
struct TreeNode* pop(struct Stack* stack) {
    if (isEmpty(stack))
        return NULL;
    return stack->array[stack->top--];
}

// Create a new tree node
struct TreeNode* createNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Insert a new node into the tree
struct TreeNode* insertNode(struct TreeNode* root, int data) {
    if (root == NULL)
        return createNode(data);
    struct TreeNode* temp = root;
    struct TreeNode* parent = NULL;
    while (temp != NULL) {
        parent = temp;
        if (data < temp->data)
            temp = temp->left;
        else
            temp = temp->right;
    }
    if (data < parent->data)
        parent->left = createNode(data);
    else
        parent->right = createNode(data);
    return root;
}

// Preorder Traversal (Non-Recursive)
void preorderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;
    struct Stack* stack = createStack();
    push(stack, root);
    while (!isEmpty(stack)) {
        struct TreeNode* current = pop(stack);
        printf("%d ", current->data);
        if (current->right != NULL)
            push(stack, current->right);
        if (current->left != NULL)
            push(stack, current->left);
    }
}

// Count Leaf Nodes
int countLeafNodes(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    struct Stack* stack = createStack();
    push(stack, root);
    int count = 0;
    while (!isEmpty(stack)) {
        struct TreeNode* current = pop(stack);
        if (current->right != NULL)
            push(stack, current->right);
        if (current->left != NULL)
            push(stack, current->left);
        if (current->left == NULL && current->right == NULL)
            count++;
    }
    return count;
}

// Count total no. of nodes
int countTotalNodes(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    struct Stack* stack = createStack();
    push(stack, root);
    int count = 0;
    while (!isEmpty(stack)) {
        struct TreeNode* current = pop(stack);
        count++;
        if (current->right != NULL)
            push(stack, current->right);
        if (current->left != NULL)
            push(stack, current->left);
    }
    return count;
}

// Utility function to find maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Display height of a tree
int height(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    struct Stack* stack = createStack();
    push(stack, root);
    int height = 0;
    while (1) {
        int nodeCount = stack->top + 1;
        if (nodeCount == 0)
            return height;
        height++;
        while (nodeCount > 0) {
            struct TreeNode* current = pop(stack);
            if (current->right != NULL)
                push(stack, current->right);
            if (current->left != NULL)
                push(stack, current->left);
            nodeCount--;
        }
    }
}

// Driver program
int main() {
    struct TreeNode* root = NULL;
    root = insertNode(root, 10);
    insertNode(root, 5);
    insertNode(root, 20);
    insertNode(root, 3);
    insertNode(root, 7);
    insertNode(root, 15);
    insertNode(root, 25);

    printf("Preorder Traversal: ");
    preorderTraversal(root);
    printf("\n");

    printf("Number of Leaf Nodes: %d\n", countLeafNodes(root));

    printf("Total number of nodes: %d\n", countTotalNodes(root));

    printf("Height of the tree: %d\n", height(root));

    return 0;
}
