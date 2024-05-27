#include <stdio.h>

// Employee structure
typedef struct {
    char employee_name[50];
    int emp_no;
    float emp_salary;
} Employee;

// Partition function for Employee structures based on emp_no
int partition(Employee a[], int low, int high, int *swapCount) {
    Employee pivot = a[low];
    int i = low + 1;
    int j = high;
    Employee c;
    while (i <= j) {
        while (i <= j && a[i].emp_no <= pivot.emp_no) {
            i++;
        }
        while (i <= j && a[j].emp_no > pivot.emp_no) {
            j--;
        }
        if (i >= j) {
            break;
        }
        // Swap
        c = a[i];
        a[i] = a[j];
        a[j] = c;
        (*swapCount)++;
    }
    // Swap pivot
    c = a[low];
    a[low] = a[j];
    a[j] = c;
    (*swapCount)++;
    return j;
}

// Quick Sort function for Employee structures
void quickSort(Employee a[], int low, int high, int *swapCount) {
    if (low < high) {
        int p = partition(a, low, high, swapCount);
        quickSort(a, low, p - 1, swapCount);
        quickSort(a, p + 1, high, swapCount);
    }
}

int main() {
    int n;
    printf("Enter size : ");
    scanf("%d", &n);

    // Array of Employee structures
    Employee a[n];

    // Input Employee details
    for (int i = 0; i < n; i++) {
        printf("Enter employee name: ");
        scanf("%s", a[i].employee_name);
        printf("Enter employee number: ");
        scanf("%d", &a[i].emp_no);
        printf("Enter employee salary: ");
        scanf("%f", &a[i].emp_salary);
    }

    int swapCount = 0; // Initialize swap count
    quickSort(a, 0, n - 1, &swapCount);

    // Output sorted Employee details
    printf("Sorted Employee details based on emp_no:\n");
    for (int i = 0; i < n; i++) {
        printf("Name: %s, Emp No: %d, Salary: %.2f\n", a[i].employee_name, a[i].emp_no, a[i].emp_salary);
    }
    printf("Number of swaps performed: %d\n", swapCount);

    return 0;
}
