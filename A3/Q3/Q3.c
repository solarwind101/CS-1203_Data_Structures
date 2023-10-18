#include <stdio.h>
#include <stdlib.h>

#define ARRSIZE 12

int cp1, cmp1, swpcnt, cmpcnt;

void merge(int arr[], int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++) {
        L[i] = arr[l + i];
        cp1++;
    }
    for (j = 0; j < n2; j++) {
        R[j] = arr[m + 1 + j];
        cp1++;
    }

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2) {
        cmp1++;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
        cp1++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
        cp1++;
    }
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void swap(int* a, int* b) {
    int t = *a;
    *a = *b;
    *b = t;
    swpcnt++;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        cmpcnt++;
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest]) {
        cmp1++;
        largest = left;
    }

    if (right < n && arr[right] > arr[largest]) {
        cmp1++;
        largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
        swpcnt++;
    }
}

void printArray(int A[], int size) {
    int i;
    for (i = 0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

int main() {
    int arr[] = {8, 19, 9, 11, 12, 11, 13, 5, 6, 7, 3, 17};
    int arr_size = ARRSIZE;

    cp1 = 0;
    cmp1 = 0;
    swpcnt = 0;
    cmpcnt = 0;

    printf("Given array is\n");
    printArray(arr, arr_size);

    int mergeSortArr[arr_size];
    int quickSortArr[arr_size];
    int heapSortArr[arr_size];

    for (int i = 0; i < arr_size; i++) {
        mergeSortArr[i] = arr[i];
        quickSortArr[i] = arr[i];
        heapSortArr[i] = arr[i];
    }

    mergeSort(mergeSortArr, 0, arr_size - 1);
    printf("\nSorted array using Merge Sort is\n");
    printArray(mergeSortArr, arr_size);
    printf("Merge Sort: Copy count %d, Comparison Count %d\n", cp1, cmp1);

    quickSort(quickSortArr, 0, arr_size - 1);
    printf("\nSorted array using Quick Sort is\n");
    printArray(quickSortArr, arr_size);
    printf("Quick Sort: Swap %d Comparison %d\n", swpcnt, cmpcnt);

    heapSort(heapSortArr, arr_size);
    printf("\nSorted array using Heap Sort is\n");
    printArray(heapSortArr, arr_size);
    printf("Heap Sort: Swap %d Comparison %d\n", swpcnt, cmpcnt);

    return 0;
}
