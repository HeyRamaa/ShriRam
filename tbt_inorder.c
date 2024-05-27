#include <stdio.h>
#include <stdlib.h>

// Structure of a node of threaded binary tree
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

// Function to traverse the threaded binary tree in inorder
void inorderTraversal(struct Node* root) {
    if (root == NULL)
        return;
    
    // Find the leftmost node
    while (root->left != NULL)
        root = root->left;
    
    // Traverse the tree using threads
    while (root != NULL) {
        // Print current node
        printf("%d ", root->data);
        
        // If the right pointer is a thread, move to the threaded node
        if (root->isThreaded)
            root = root->right;
        else {
            // Otherwise, move to the leftmost child of the right subtree
            root = root->right;
            while (root != NULL && root->left != NULL)
                root = root->left;
        }
    }
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
    
    // Traverse the threaded binary tree in inorder
    printf("Inorder Traversal: ");
    inorderTraversal(root);
    printf("\n");
    
    return 0;
}
