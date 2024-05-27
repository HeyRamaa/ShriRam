#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* left;
    struct Node* right;
    int isThreaded; // Flag to indicate if the right pointer is a thread or not
};

// Function to create a new Node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->isThreaded = 0; // Initially, the right pointer is not a thread
    return node;
}

// Function to perform inorder threading
void inorderThreaded(struct Node* root, struct Node** prev) {
    if (root == NULL)
        return;
    
    // Recur for left subtree
    inorderThreaded(root->left, prev);
    
    // If the previous node exists and its right child is NULL
    if (*prev != NULL && (*prev)->right == NULL) {
        // Make the right pointer of the previous node point to the current node
        (*prev)->right = root;
        // Set the flag indicating that the right pointer is a thread
        (*prev)->isThreaded = 1;
    }

    // Set the previous node to the current node
    *prev = root;
    
    // Recur for right subtree
    inorderThreaded(root->right, prev);
}

// Function to traverse the threaded binary tree in preorder
void preorderTraversal(struct Node* root) {
    if (root == NULL)
        return;
    
    // Print the current node
    printf("%d ", root->data);
    
    // If the right pointer is a thread, move to the next threaded node
    if (root->isThreaded)
        root = root->right;
    else {
        // Otherwise, move to the left child
        preorderTraversal(root->left);
    }
    
    // Recur for the rest of the tree
    preorderTraversal(root->right);
}

// Driver program to test above functions
int main() {
    // Constructing the binary tree
    struct Node* root = newNode(1);
    root->left = newNode(2);
    root->right = newNode(3);
    root->left->left = newNode(4);
    root->left->right = newNode(5);
    root->right->left = newNode(6);
    root->right->right = newNode(7);
    
    // Perform inorder threading
    struct Node* prev = NULL;
    inorderThreaded(root, &prev);
    
    // Traverse the threaded binary tree in preorder
    printf("Preorder Traversal: ");
    preorderTraversal(root);
    printf("\n");
    
    return 0;
}
