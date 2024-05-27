#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
    int height;
} Node;

int max(int a, int b) {
    return (a > b) ? a : b;
}

int height(Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

Node *newNode(int data) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    node->height = 1;
    return node;
}

Node *rightRotate(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

Node *leftRotate(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(Node *N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

Node *insert(Node *node, int data) {
    if (node == NULL)
        return newNode(data);

    if (data < node->data)
        node->left = insert(node->left, data);
    else if (data > node->data)
        node->right = insert(node->right, data);
    else
        return node;

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    if (balance > 1 && data < node->left->data)
        return rightRotate(node);

    if (balance < -1 && data > node->right->data)
        return leftRotate(node);

    if (balance > 1 && data > node->left->data) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && data < node->right->data) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

void printLevelOrder(Node *root, int level) {
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->data);
    else if (level > 1) {
        printLevelOrder(root->left, level - 1);
        printLevelOrder(root->right, level - 1);
    }
}

int heightTree(Node *node) {
    if (node == NULL)
        return 0;
    else {
        int leftHeight = heightTree(node->left);
        int rightHeight = heightTree(node->right);

        if (leftHeight > rightHeight)
            return (leftHeight + 1);
        else
            return (rightHeight + 1);
    }
}

void printLevelWise(Node *root) {
    int h = heightTree(root);
    int i;
    for (i = 1; i <= h; i++) {
        printLevelOrder(root, i);
        printf("\n");
    }
}

int main() {
    Node *root = NULL;
    int data;
    char choice[2];

    while (1) {
        printf("1. Insert Node\n");
        printf("2. Display AVL Tree Level-wise\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%s", choice);

        if (choice[0] == '1') {
            printf("Enter data to insert:\n ");
            scanf("%d", &data);
            root = insert(root, data);
        } else if (choice[0] == '2') {
            printf("AVL Tree Level-wise:\n");
            printLevelWise(root);
        } else if (choice[0] == '3') {
            printf("Exiting program...\n");
            break;
        } else {
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}
