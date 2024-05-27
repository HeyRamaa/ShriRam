#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a structure for a binary tree node
struct TreeNode {
    int data;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new binary tree node
struct TreeNode* createTreeNode(int data) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->data = data;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a key into the BST
struct TreeNode* insert(struct TreeNode* root, int key) {
    if (root == NULL)
        return createTreeNode(key);
    if (key < root->data)
        root->left = insert(root->left, key);
    else if (key > root->data)
        root->right = insert(root->right, key);
    return root;
}

// Function to perform preorder traversal of the BST
void preorderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;
    
    struct TreeNode* stack[100]; // Stack for preorder traversal
    int top = -1;
    struct TreeNode* current = root;
    
    printf("Preorder Traversal: ");
    while (current != NULL || top != -1) {
        while (current != NULL) {
            printf("%d ", current->data);
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        current = current->right;
    }
    printf("\n");
}

// Function to count total number of nodes in the BST
int countNodes(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    
    int nodeCount = 0;
    struct TreeNode* stack[100]; // Stack for preorder traversal
    int top = -1;
    struct TreeNode* current = root;
    
    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            nodeCount++;
            current = current->left;
        }
        current = stack[top--];
        current = current->right;
    }
    return nodeCount;
}

// Function to display leaf nodes of the BST
void displayLeafNodes(struct TreeNode* root) {
    if (root == NULL)
        return;
    
    struct TreeNode* stack[100]; // Stack for inorder traversal
    int top = -1;
    struct TreeNode* current = root;
    
    printf("Leaf Nodes: ");
    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        if (current->left == NULL && current->right == NULL)
            printf("%d ", current->data);
        current = current->right;
    }
    printf("\n");
}

int main() {
    // Create a Binary Search Tree
    struct TreeNode* root = NULL;
    root = insert(root, 5);
    insert(root, 3);
    insert(root, 7);
    insert(root, 2);
    insert(root, 4);
    insert(root, 6);
    insert(root, 8);
    
    // Perform non-recursive operations
    preorderTraversal(root);
    printf("Total Number of Nodes: %d\n", countNodes(root));
    displayLeafNodes(root);
    
    // Free memory
    free(root);
    
    return 0;
}
