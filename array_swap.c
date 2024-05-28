#include <stdio.h>

// Function to find the swapped elements in the array
void findSwappedElements(int A[], int n, int *x, int *y) {
    int i;
    *x = -1;  // Initialize x to an invalid index
    *y = -1;  // Initialize y to an invalid index

    // Traverse the array to find the first pair of elements where order is violated
    for (i = 0; i < n - 1; i++) {
        if (A[i] > A[i + 1]) {
            if (*x == -1) {
                *x = i;
            } else {
                *y = i + 1;
                break;
            }
        }
    }
    
    // If the second violation was not found, set y to x + 1
    if (*y == -1) {
        *y = *x + 1;
    }
}

int main() {
    int A[] = {10, 2, 6, 4, 5, 3, 7};
    int n = sizeof(A) / sizeof(A[0]);
    int x, y;

    findSwappedElements(A, n, &x, &y);

    printf("The swapped elements are %d and %d at positions %d and %d\n", A[x], A[y], x, y);

    return 0;
}
