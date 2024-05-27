#include <stdio.h>

void findSwappedPair(int arr[], int n) {
    int firstIndex = -1, secondIndex = -1;

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
    int temp = arr[firstIndex];
    arr[firstIndex] = arr[secondIndex];
    arr[secondIndex] = temp;

    printf("Swapped elements: %d and %d\n", arr[firstIndex], arr[secondIndex]);
    printf("Their positions: %d and %d\n", firstIndex, secondIndex);
}

int main() {
    int arr[] = {1, 4, 3, 2, 5};
    int n = sizeof(arr) / sizeof(arr[0]);

    findSwappedPair(arr, n);

    return 0;
}
