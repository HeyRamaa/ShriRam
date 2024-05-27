#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h> // Include string.h for strcpy function

// Define a structure for an employee record
struct Employee {
    int emp_id;
    char name[50];
    // Add other fields as needed
    // For simplicity, let's assume only emp_id and name are present
    struct Employee* left;
    struct Employee* right;
};

// Function to create a new employee record
struct Employee* createEmployee(int emp_id, const char* name) {
    struct Employee* newEmployee = (struct Employee*)malloc(sizeof(struct Employee));
    newEmployee->emp_id = emp_id;
    strcpy(newEmployee->name, name); // Use strcpy function to copy the name
    newEmployee->left = NULL;
    newEmployee->right = NULL;
    return newEmployee;
}

// Function to insert an employee record into the BST
struct Employee* insert(struct Employee* root, int emp_id, const char* name) {
    if (root == NULL)
        return createEmployee(emp_id, name);
    if (emp_id < root->emp_id)
        root->left = insert(root->left, emp_id, name);
    else if (emp_id > root->emp_id)
        root->right = insert(root->right, emp_id, name);
    return root;
}

// Function to search for an employee record based on emp_id
struct Employee* search(struct Employee* root, int emp_id) {
    if (root == NULL || root->emp_id == emp_id)
        return root;
    if (emp_id < root->emp_id)
        return search(root->left, emp_id);
    return search(root->right, emp_id);
}

// Function to traverse the BST in inorder (sorted order)
void inorderTraversal(struct Employee* root) {
    if (root != NULL) {
        inorderTraversal(root->left);
        printf("Emp ID: %d, Name: %s\n", root->emp_id, root->name);
        inorderTraversal(root->right);
    }
}

int main() {
    // Sample employee records
    struct Employee* root = NULL;
    root = insert(root, 101, "John");
    insert(root, 102, "Alice");
    insert(root, 103, "Bob");
    insert(root, 104, "Emily");
    insert(root, 105, "Michael");

    // Search for an employee record by emp_id
    int emp_id_to_search = 103;
    struct Employee* found_employee = search(root, emp_id_to_search);
    if (found_employee != NULL) {
        printf("Employee Record Found:\n");
        printf("Emp ID: %d, Name: %s\n", found_employee->emp_id, found_employee->name);
    } else {
        printf("Employee Record with Emp ID %d Not Found\n", emp_id_to_search);
    }

    // Display the employee records in sorted order
    printf("\nEmployee Records (Sorted by Emp ID):\n");
    inorderTraversal(root);

    // Free memory
    // You may need to implement a function to free the memory of all nodes in the BST

    return 0;
}
