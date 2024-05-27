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

// Function to perform inorder traversal of the BST
void inorderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;
    
    struct TreeNode* stack[100]; // Stack for inorder traversal
    int top = -1;
    struct TreeNode* current = root;
    
    printf("Inorder Traversal: ");
    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        printf("%d ", current->data);
        current = current->right;
    }
    printf("\n");
}

// Function to display the number of leaf nodes in the BST
int countLeafNodes(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    
    int leafCount = 0;
    struct TreeNode* stack[100]; // Stack for inorder traversal
    int top = -1;
    struct TreeNode* current = root;
    
    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        current = stack[top--];
        if (current->left == NULL && current->right == NULL)
            leafCount++;
        current = current->right;
    }
    return leafCount;
}

// Function to create the mirror image of the BST
struct TreeNode* mirrorImage(struct TreeNode* root) {
    if (root == NULL)
        return NULL;
    
    struct TreeNode* temp = root->left;
    root->left = mirrorImage(root->right);
    root->right = mirrorImage(temp);
    return root;
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
    inorderTraversal(root);
    printf("Number of Leaf Nodes: %d\n", countLeafNodes(root));
    
    // Create mirror image of the BST
    printf("Creating Mirror Image...\n");
    struct TreeNode* mirrorRoot = mirrorImage(root);
    printf("Mirror Image created.\n");
    
    // Display the mirror image
    inorderTraversal(mirrorRoot);
    
    // Free memory
    free(root);
    free(mirrorRoot);
    
    return 0;
}
