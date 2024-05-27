#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure to represent a Student
struct Student {
    char student_name[50];
    int student_roll_no;
    int total_marks;
};
// Function to swap two Student structures
void swap(struct Student* a, struct Student* b, int* swapCount) {
    struct Student temp = *a;
    *a = *b;
    *b = temp;
    (*swapCount)++;
}
// Function to heapify a subtree rooted with node i
void heapify(struct Student arr[], int n, int i, int* swapCount) {
    int largest = i; // Initialize largest as root
    int l = 2 * i + 1; // left = 2*i + 1
    int r = 2 * i + 2; // right = 2*i + 2

    // If left child is larger than root
    if (l < n && arr[l].student_roll_no > arr[largest].student_roll_no)
        largest = l;

    // If right child is larger than largest so far
    if (r < n && arr[r].student_roll_no > arr[largest].student_roll_no)
        largest = r;

    // If largest is not root
    if (largest != i) {
        swap(&arr[i], &arr[largest], swapCount);

        // Recursively heapify the affected sub-tree
        heapify(arr, n, largest, swapCount);
    }
}

// Main function to do heap sort
void heapSort(struct Student arr[], int n, int* swapCount) {
    // Build heap (rearrange array)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i, swapCount);

    // One by one extract an element from heap
    for (int i = n - 1; i > 0; i--) {
        // Move current root to end
        swap(&arr[0], &arr[i], swapCount);

        // call max heapify on the reduced heap
        heapify(arr, i, 0, swapCount);
    }
}

// Function to print the sorted array of students
void printArray(struct Student arr[], int n) {
    printf("Sorted array of students by roll number:\n");
    printf("Name\t\tRoll No.\tTotal Marks\n");
    for (int i = 0; i < n; ++i)
        printf("%s\t\t%d\t\t%d\n", arr[i].student_name, arr[i].student_roll_no, arr[i].total_marks);
}

int main() {
    int n, swapCount = 0;
    printf("Enter the number of students: ");
    scanf("%d", &n);
    struct Student* students = (struct Student*)malloc(n * sizeof(struct Student));

    // Input student details
    for (int i = 0; i < n; ++i) {
        printf("Enter name of student %d: ", i + 1);
        scanf("%s", students[i].student_name);
        printf("Enter roll number of student %d: ", i + 1);
        scanf("%d", &students[i].student_roll_no);
        printf("Enter total marks of student %d: ", i + 1);
        scanf("%d", &students[i].total_marks);
    }

    // Perform Heap Sort
    heapSort(students, n, &swapCount);

    // Print sorted array and number of swaps
    printArray(students, n);
    printf("Number of swaps performed: %d\n", swapCount);

    free(students);
    return 0;
}
