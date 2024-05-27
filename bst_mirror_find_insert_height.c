#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Define a structure for a binary tree node
struct TreeNode {
    int key;
    struct TreeNode *left;
    struct TreeNode *right;
};

// Function to create a new binary tree node
struct TreeNode* createTreeNode(int key) {
    struct TreeNode* newNode = (struct TreeNode*)malloc(sizeof(struct TreeNode));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a key into the BST
struct TreeNode* insert(struct TreeNode* root, int key) {
    if (root == NULL)
        return createTreeNode(key);
    if (key < root->key)
        root->left = insert(root->left, key);
    else if (key > root->key)
        root->right = insert(root->right, key);
    return root;
}

// Function to create the mirror image of a BST
struct TreeNode* mirrorImage(struct TreeNode* root) {
    if (root == NULL)
        return NULL;
    struct TreeNode* mirroredRoot = createTreeNode(root->key);
    mirroredRoot->left = mirrorImage(root->right);
    mirroredRoot->right = mirrorImage(root->left);
    return mirroredRoot;
}

// Function to find a key in the BST
bool find(struct TreeNode* root, int key) {
    if (root == NULL)
        return false;
    if (root->key == key)
        return true;
    else if (key < root->key)
        return find(root->left, key);
    else
        return find(root->right, key);
}

// Function to calculate the height of the BST
int height(struct TreeNode* root) {
    if (root == NULL)
        return -1; // Height of an empty tree is -1
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
}

// Function to display the menu
void displayMenu() {
    printf("\nMenu:\n");
    printf("1. Insert\n");
    printf("2. Mirror Image\n");
    printf("3. Find\n");
    printf("4. Height of the tree\n");
    printf("5. Exit\n");
}

int main() {
    struct TreeNode* root = NULL;
    int choice, key;
    while (true) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter key to insert: ");
                scanf("%d", &key);
                root = insert(root, key);
                break;
            case 2:
                printf("Creating Mirror Image...\n");
                root = mirrorImage(root);
                printf("Mirror Image created.\n");
                break;
            case 3:
                printf("Enter key to find: ");
                scanf("%d", &key);
                if (find(root, key))
                    printf("Key %d is found.\n", key);
                else
                    printf("Key %d is not found.\n", key);
                break;
            case 4:
                printf("Height of the tree: %d\n", height(root));
                break;
            case 5:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a valid option.\n");
        }
    }
    return 0;
}

