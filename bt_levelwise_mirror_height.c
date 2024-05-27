#include <stdio.h>
#include <stdlib.h>

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

// Function for level-wise display of the binary tree
void levelOrderDisplay(struct TreeNode* root) {
    if (root == NULL)
        return;
    struct TreeNode* queue[100]; // Assuming maximum 100 nodes in the binary tree
    int front = 0, rear = 0;
    queue[rear++] = root;
    while (front < rear) {
        struct TreeNode* current = queue[front++];
        printf("%d ", current->data);
        if (current->left != NULL)
            queue[rear++] = current->left;
        if (current->right != NULL)
            queue[rear++] = current->right;
    }
}

// Function to swap left and right subtrees to create mirror image of the binary tree
void mirrorImage(struct TreeNode* root) {
    if (root == NULL)
        return;
    struct TreeNode* temp = root->left;
    root->left = root->right;
    root->right = temp;
    mirrorImage(root->left);
    mirrorImage(root->right);
}

// Function to calculate the height of the binary tree
int calculateHeight(struct TreeNode* root) {
    if (root == NULL)
        return 0;
    int leftHeight = calculateHeight(root->left);
    int rightHeight = calculateHeight(root->right);
    return (leftHeight > rightHeight) ? (leftHeight + 1) : (rightHeight + 1);
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

    // Perform operations
    printf("a. Level-wise Display: ");
    levelOrderDisplay(root);
    printf("\n");

    printf("b. Mirror Image: ");
    mirrorImage(root);
    levelOrderDisplay(root);
    printf("\n");

    printf("c. Height of the tree: %d\n", calculateHeight(root));

    return 0;
}
