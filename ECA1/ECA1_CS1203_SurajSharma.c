#include <stdio.h>

// Function to swap two integers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to reverse an array from a given start and end index
void reverse(int arr[], int start, int end) {
    while (start < end) {
        swap(&arr[start], &arr[end]);
        start++;
        end--;
    }
}

// Function to generate the next permutation in lexicographic order
int next_permutation(int arr[], int n) {
    // Find the rightmost pair of adjacent elements that are in ascending order
    int i = n - 2;
    while (i >= 0 && arr[i] >= arr[i + 1]) {
        i--;
    }

    // If no such pair exists, all permutations have been generated
    if (i < 0) {
        return 0;
    }

    // Find the next element that is greater than arr[i]
    int j = n - 1;
    while (arr[j] <= arr[i]) {
        j--;
    }

    // Swap arr[i] and arr[j]
    swap(&arr[i], &arr[j]);

    // Reverse the sub-array from i + 1 to n - 1
    reverse(arr, i + 1, n - 1);

    return 1;
}

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);

    // Initialize array with numbers from 1 to n
    int arr[n];
    for (int i = 0; i < n; i++) {
        arr[i] = i + 1;
    }

    // Generate and print all permutations
    do {
        for (int i = 0; i < n; i++) {
            printf("%d ", arr[i]);
        }
        printf("\n");
    } while (next_permutation(arr, n));

    return 0;
}
