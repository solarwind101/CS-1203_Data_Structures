#include <stdio.h>

// Implementation of Insertion Sort
void insertionSort(int a[], int n, long long *comparisons, long long *swaps) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = a[i];
        j = i - 1;

        while (j >= 0 && a[j] > key) {
            (*comparisons)++;
            a[j + 1] = a[j];
            (*swaps)++;
            j--;
        }
        if (j >= 0) {
            (*comparisons)++;
        }

        a[j + 1] = key;
        (*swaps)++;
    }
}

// Implementation of Bubble Sort
void bubbleSort(int a[], int n, long long *comparisons, long long *swaps) {
    int i, j;
    for (i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            (*comparisons)++;
            if (a[j] > a[j + 1]) {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
                (*swaps)++;
            }
        }
    }
}

// Function to print the elements of the array
void printArr(int a[], int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", a[i]);
    }
    printf("\n");
}

int main() {
    int a[] = {11, 84, 8, 72, 64, 25, 53, 46, 39, 97}; // Array of size 10
    int a2[] = {11, 84, 8, 72, 64, 25, 53, 46, 39, 97}; // Array of size 10


    int n = sizeof(a) / sizeof(a[0]);
    
    // Variables to count comparisons and swaps
    long long comparisons_insertion = 0, swaps_insertion = 0;
    long long comparisons_bubble = 0, swaps_bubble = 0;

    // Using Insertion Sort
    printf("====Insertion Sort====\n\n");

    printf("Before sorting, array elements are -\n");
    printArr(a, n);

    insertionSort(a, n, &comparisons_insertion, &swaps_insertion);

    printf("\nAfter sorting, array elements are -\n");
    printArr(a, n);

    printf("\nComparisons (Insertion Sort): %lld\n", comparisons_insertion);
    printf("Swaps (Insertion Sort): %lld\n\n", swaps_insertion);

    // Using Bubble Sort
    printf("=======Bubble Sort=======\n\n");

    printf("Before sorting, array elements are -\n");
    printArr(a2, n);

    bubbleSort(a2, n, &comparisons_bubble, &swaps_bubble);

    printf("\nAfter sorting, array elements are -\n");
    printArr(a2, n);

    printf("\nComparisons (Bubble Sort): %lld\n", comparisons_bubble);
    printf("Swaps (Bubble Sort): %lld\n", swaps_bubble);

    return 0;
}
