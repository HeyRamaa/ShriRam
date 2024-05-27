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

// Function for non-recursive postorder traversal of the BST
void postorderTraversal(struct TreeNode* root) {
    if (root == NULL)
        return;

    struct TreeNode* stack[100]; // Stack for postorder traversal
    int top = -1;
    struct TreeNode* current = root;
    struct TreeNode* lastVisitedNode = NULL;

    printf("Non-recursive Postorder Traversal: ");
    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            current = current->left;
        }
        struct TreeNode* temp = stack[top]->right;
        if (temp == NULL || temp == lastVisitedNode) {
            lastVisitedNode = stack[top--];
            printf("%d ", lastVisitedNode->data);
        } else {
            current = temp;
        }
    }
    printf("\n");
}

// Function to display the tree
void displayTree(struct TreeNode* root) {
    if (root == NULL)
        return;

    printf("%d ", root->data);
    displayTree(root->left);
    displayTree(root->right);
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

    // Display the initial tree
    printf("Initial Tree (Preorder Traversal): ");
    displayTree(root);
    printf("\n");

    // Perform deletion
    int keyToDelete = 3;
    printf("Deleting node with key %d...\n", keyToDelete);
    root = deleteNode(root, keyToDelete);

    // Display the tree after deletion
    printf("Tree after deletion (Preorder Traversal): ");
    displayTree(root);
    printf("\n");

    // Perform non-recursive postorder traversal
    postorderTraversal(root);

    // Free memory
    free(root);

    return 0;
}
