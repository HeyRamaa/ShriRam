#include <stdio.h>
#include <stdlib.h>

// Structure for a node of AVL tree
struct AVLNode {
    int data;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
};

// Function to get the height of a node
int height(struct AVLNode *node) {
    if (node == NULL)
        return 0;
    return node->height;
}

// Function to calculate the balance factor of a node
int balanceFactor(struct AVLNode *node) {
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to create a new node with given data
struct AVLNode *newNode(int data) {
    struct AVLNode *node = (struct AVLNode *)malloc(sizeof(struct AVLNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // New node is initially at height 1
    return node;
}

// Function to perform right rotation
struct AVLNode *rightRotate(struct AVLNode *y) {
    struct AVLNode *x = y->left;
    struct AVLNode *T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

// Function to perform left rotation
struct AVLNode *leftRotate(struct AVLNode *x) {
    struct AVLNode *y = x->right;
    struct AVLNode *T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

// Function to insert a new node with given key into AVL tree
struct AVLNode *insert(struct AVLNode *node, int data) {
    // Perform standard BST insertion
    if (node == NULL)
        return newNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else // Equal keys are not allowed in AVL tree
        return node;

    // Update height of this ancestor node
    node->height = 1 + (height(node->left) > height(node->right) ? height(node->left) : height(node->right));

    // Get the balance factor of this ancestor node to check whether this node became unbalanced
    int balance = balanceFactor(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // If the node is balanced, return the unchanged node pointer
    return node;
}

// Function to print AVL tree level-wise
void printLevel(struct AVLNode *root, int level) {
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->data);
    else if (level > 1) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

// Function to find the height of the AVL tree
int treeHeight(struct AVLNode *node) {
    if (node == NULL)
        return 0;
    else {
        // Compute the height of each subtree
        int leftHeight = treeHeight(node->left);
        int rightHeight = treeHeight(node->right);

        // Use the larger one
        if (leftHeight > rightHeight)
            return (leftHeight + 1);
        else
            return (rightHeight + 1);
    }
}

// Function to print AVL tree level-wise
void printAVLLevel(struct AVLNode *root) {
    int h = treeHeight(root);
    int i;
    for (i = 1; i <= h; i++) {
        printLevel(root, i);
        printf("\n");
    }
}

// Driver program to test above functions
int main() {
    struct AVLNode *root = NULL;
    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    printf("AVL Tree after insertion:\n");
    printAVLLevel(root);

    return 0;
}
