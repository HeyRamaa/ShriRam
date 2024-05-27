#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a structure for a binary tree node
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Define a structure for a queue node
struct QueueNode {
    struct TreeNode *treeNode;
    struct QueueNode *next;
};

// Define a structure for a queue
struct Queue {
    struct QueueNode *front, *rear;
    int count;
};

// Function to create a new binary tree node
struct TreeNode* createTreeNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to create an empty queue
struct Queue* createQueue() {
    struct Queue* queue = (struct Queue*)malloc(sizeof(struct Queue));
    queue->front = queue->rear = NULL;
    queue->count = 0;
    return queue;
}

// Function to check if the queue is empty
bool isEmpty(struct Queue* queue) {
    return (queue->front == NULL);
}

// Function to enqueue a binary tree node to the queue
void enqueue(struct Queue* queue, struct TreeNode *treeNode) {
    struct QueueNode* newNode = (struct QueueNode*)malloc(sizeof(struct QueueNode));
    newNode->treeNode = treeNode;
    newNode->next = NULL;
    if (isEmpty(queue)) {
        queue->front = queue->rear = newNode;
    } else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
    queue->count++;
}

// Function to dequeue a binary tree node from the queue
struct TreeNode* dequeue(struct Queue* queue) {
    if (isEmpty(queue))
        return NULL;
    struct TreeNode* temp = queue->front->treeNode;
    struct QueueNode* tempNode = queue->front;
    queue->front = queue->front->next;
    if (queue->front == NULL)
        queue->rear = NULL;
    free(tempNode);
    queue->count--;
    return temp;
}

// Function for level-wise traversal of the binary tree
void levelOrderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;
    struct Queue* queue = createQueue();
    enqueue(queue, root);
    while (!isEmpty(queue)) {
        struct TreeNode* current = dequeue(queue);
        printf("%d ", current->data);
        if (current->left != NULL)
            enqueue(queue, current->left);
        if (current->right != NULL)
            enqueue(queue, current->right);
    }
}

// Function to display leaf nodes of the binary tree
void displayLeafNodes(struct TreeNode* root) {
    if (root == NULL)
        return;
    struct Queue* queue = createQueue();
    enqueue(queue, root);
    printf("Leaf Nodes: ");
    while (!isEmpty(queue)) {
        struct TreeNode* current = dequeue(queue);
        if (current->left == NULL && current->right == NULL)
            printf("%d ", current->data);
        if (current->left != NULL)
            enqueue(queue, current->left);
        if (current->right != NULL)
            enqueue(queue, current->right);
    }
}

// Function to count total number of leaf nodes in the binary tree
int countLeafNodes(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    struct Queue* queue = createQueue();
    enqueue(queue, root);
    int count = 0;
    while (!isEmpty(queue)) {
        struct TreeNode* current = dequeue(queue);
        if (current->left == NULL && current->right == NULL)
            count++;
        if (current->left != NULL)
            enqueue(queue, current->left);
        if (current->right != NULL)
            enqueue(queue, current->right);
    }
    return count;
}

// Function to calculate the height of the binary tree
int calculateHeight(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    struct Queue* queue = createQueue();
    enqueue(queue, root);
    int height = 0;
    while (1) {
        int nodeCount = queue->count;
        if (nodeCount == 0)
            return height;
        height++;
        while (nodeCount > 0) {
            struct TreeNode* current = dequeue(queue);
            if (current->left != NULL)
                enqueue(queue, current->left);
            if (current->right != NULL)
                enqueue(queue, current->right);
            nodeCount--;
        }
    }
}

int main() {
    // Create a binary tree
    struct TreeNode* root = createTreeNode(1);
    root->left = createTreeNode(2);
    root->right = createTreeNode(3);
    root->left->left = createTreeNode(4);
    root->left->right = createTreeNode(5);
    root->right->left = createTreeNode(6);
    root->right->right = createTreeNode(7);

    // Perform operations
    printf("a. Level-wise Traversal: ");
    levelOrderTraversal(root);
    printf("\n");

    displayLeafNodes(root);
    printf("\n");

    printf("c. Total number of Leaf nodes: %d\n", countLeafNodes(root));

    printf("d. Height of the tree: %d\n", calculateHeight(root));

    return 0;
}
