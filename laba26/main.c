#include "merge_sort.h"
#include <stdio.h>

int main() {
    int arr[] = {38, 27, 43, 3, 9, 82, 10};
    int size = sizeof(arr) / sizeof(arr[0]);

    printf("Original array:\n");
    printArray(arr, size);

    mergeSort(arr, 0, size - 1);

    printf("Sorted array (Merge Sort):\n");
    printArray(arr, size);

    return 0;
}