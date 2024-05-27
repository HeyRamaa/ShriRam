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

// Function to find the minimum value node in a BST
struct TreeNode* minValueNode(struct TreeNode* node) {
    struct TreeNode* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a key from the BST
struct TreeNode* deleteNode(struct TreeNode* root, int key) {
    if (root == NULL)
        return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            struct TreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct TreeNode* temp = root->left;
            free(root);
            return temp;
        }
        struct TreeNode* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to find the height of the BST
int height(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
}

// Function to print nodes at a given level
void printLevel(struct TreeNode* root, int level) {
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->data);
    else if (level > 1) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

// Function to print level order traversal of the BST
void levelOrderTraversal(struct TreeNode* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printf("Level %d: ", i);
        printLevel(root, i);
        printf("\n");
    }
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

    // Display the BST levelwise
    printf("Levelwise Display of the BST:\n");
    levelOrderTraversal(root);

    // Perform deletion of a node
    int keyToDelete = 3;
    printf("\nDeleting node with key %d...\n", keyToDelete);
    root = deleteNode(root, keyToDelete);

    // Display the BST after deletion
    printf("\nLevelwise Display of the BST after deletion:\n");
    levelOrderTraversal(root);

    // Free memory
    free(root);

    return 0;
}
