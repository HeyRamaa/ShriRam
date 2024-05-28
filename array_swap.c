#include <stdio.h>

// Function to identify the swapped pair of elements and their positions
void findSwappedPair(int arr[], int n) {
    int firstIndex = -1, secondIndex = -1;

    // Iterate through the array to find the swapped pair
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            if (firstIndex == -1) {
                firstIndex = i;
            } else {
                secondIndex = i + 1;
                break;
            }
        }
    }

    // Print the indices and elements of the swapped pair
    if (firstIndex != -1 && secondIndex != -1) {
        printf("Swapped pair found at positions %d and %d\n", firstIndex, secondIndex);
        printf("Elements: %d and %d\n", arr[firstIndex], arr[secondIndex]);
    } else {
        printf("No pair of elements swapped in the array.\n");
    }
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d", &n);
    
    // Assuming all elements are distinct integers
    int arr[n];
    printf("Enter the elements of the array: ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // Find the swapped pair
    findSwappedPair(arr, n);

    return 0;
}
