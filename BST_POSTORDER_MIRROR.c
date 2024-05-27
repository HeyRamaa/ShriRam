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

// Function to perform postorder traversal of the binary tree
void postorderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;
    
    // Create two stacks for postorder traversal
    struct TreeNode* stack1[100]; // Stack for nodes
    struct TreeNode* stack2[100]; // Stack for storing postorder traversal
    
    int top1 = -1, top2 = -1;
    stack1[++top1] = root;
    
    while (top1 >= 0) {
        struct TreeNode* current = stack1[top1--];
        stack2[++top2] = current;
        
        if (current->left != NULL)
            stack1[++top1] = current->left;
        if (current->right != NULL)
            stack1[++top1] = current->right;
    }
    
    // Print postorder traversal by popping elements from stack2
    printf("Postorder Traversal: ");
    while (top2 >= 0) {
        struct TreeNode* node = stack2[top2--];
        printf("%d ", node->data);
    }
    printf("\n");
}

// Function to display leaf nodes of the binary tree
void displayLeafNodes(struct TreeNode* root) {
    if (root == NULL)
        return;
    
    printf("Leaf Nodes: ");
    struct TreeNode* stack[100]; // Stack for inorder traversal
    int top = -1;
    stack[++top] = root;
    
    while (top >= 0) {
        struct TreeNode* current = stack[top--];
        
        if (current->left == NULL && current->right == NULL)
            printf("%d ", current->data);
        
        if (current->right != NULL)
            stack[++top] = current->right;
        if (current->left != NULL)
            stack[++top] = current->left;
    }
    printf("\n");
}

// Function to create the mirror image of the binary tree
struct TreeNode* mirrorImage(struct TreeNode* root) {
    if (root == NULL)
        return NULL;
    
    struct TreeNode* temp = root->left;
    root->left = mirrorImage(root->right);
    root->right = mirrorImage(temp);
    return root;
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
    
    // Perform non-recursive operations
    postorderTraversal(root);
    displayLeafNodes(root);
    
    // Create mirror image of the binary tree
    printf("Creating Mirror Image...\n");
    struct TreeNode* mirrorRoot = mirrorImage(root);
    printf("Mirror Image created.\n");
    
    // Display the mirror image
    printf("Mirror Image - Postorder Traversal: ");
    postorderTraversal(mirrorRoot);
    
    // Free memory
    free(root);
    free(mirrorRoot);
    
    return 0;
}

