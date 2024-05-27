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

    inorderTraversal(root->left);
    printf("%d ", root->data);
    inorderTraversal(root->right);
}

// Function to create the mirror image of the BST without disturbing the original tree
struct TreeNode* mirrorImage(struct TreeNode* root) {
    if (root == NULL)
        return NULL;

    struct TreeNode* mirroredRoot = createTreeNode(root->data);
    mirroredRoot->left = mirrorImage(root->right);
    mirroredRoot->right = mirrorImage(root->left);
    return mirroredRoot;
}

// Function to create the mirror image of the BST and replace the original tree with the mirror image
void mirrorImageAndReplace(struct TreeNode* root) {
    if (root == NULL)
        return;

    struct TreeNode* temp = root->left;
    root->left = mirrorImage(root->right);
    root->right = mirrorImage(temp);
}

// Function to calculate the height of the BST using non-recursive method
int height(struct TreeNode* root) {
    if (root == NULL)
        return 0;

    int maxHeight = 0;
    struct TreeNode* stack[100]; // Stack for inorder traversal
    int heights[100]; // Heights corresponding to nodes
    int top = -1;
    struct TreeNode* current = root;
    int currentHeight = 0;

    while (current != NULL || top != -1) {
        while (current != NULL) {
            stack[++top] = current;
            heights[top] = ++currentHeight;
            current = current->left;
        }
        current = stack[top--];
        currentHeight = heights[top];
        if (currentHeight > maxHeight)
            maxHeight = currentHeight;
        current = current->right;
    }
    return maxHeight;
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

    // Display the original BST
    printf("Original BST (Inorder Traversal): ");
    inorderTraversal(root);
    printf("\n");

    // Display the height of the original BST
    printf("Height of the original BST: %d\n", height(root));

    // Display the mirror image of the BST without disturbing the original tree
    printf("\nMirror Image of the BST without disturbing the original tree (Inorder Traversal): ");
    struct TreeNode* mirrorWithoutDisturb = mirrorImage(root);
    inorderTraversal(mirrorWithoutDisturb);
    printf("\n");

    // Display the mirror image of the BST and replace the original tree with it
    printf("\nMirror Image of the BST and replacing the original tree (Inorder Traversal): ");
    mirrorImageAndReplace(root);
    inorderTraversal(root);
    printf("\n");

    // Free memory
    free(root);
    free(mirrorWithoutDisturb);

    return 0;
}
