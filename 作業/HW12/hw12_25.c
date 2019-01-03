#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 500

void merge(int arr[], int left, int mid, int right);
void mergeSort(int arr[], int left, int right);

int main() {
    srand(time(NULL));

    int numbers[MAX] = {0};

    printf("Before sorting: ");
    for(int i = 0; i < MAX; i++) {
        numbers[i] = rand() % MAX;
        printf("%d ", numbers[i]);
    }

    mergeSort(numbers, 0, MAX-1);

    printf("\n\nAfter sorting: ");
    for(int i = 0; i < MAX; i++)
        printf("%d ", numbers[i]);

    printf("\n");

    return 0;
}



// Merges two subarrays of arr[]
// First subarray is arr[left...mid]
// Second subarray is arr[mid+1...right]
void merge(int arr[], int left, int mid, int right)  {
    int i, j, k;
    int leftCount = mid - left + 1;
    int rightCount = right - mid;

    // create temp arrays
    int L[leftCount], R[rightCount];

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < leftCount; i++)
        L[i] = arr[left+i];
    for (j = 0; j < rightCount; j++)
        R[j] = arr[mid+j+1];

    // Merge the temp arrays back into arr[left..right]
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = left; // Initial index of merged subarray
    while(i < leftCount && j < rightCount) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any
    while(i < leftCount) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any
    while(j < rightCount) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;

        // Sort first and second halves
        mergeSort(arr, left, mid);
        mergeSort(arr, mid+1, right);

        merge(arr, left, mid, right);
    }
}
