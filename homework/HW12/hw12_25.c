#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 100

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

void merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int leftCount = mid - left + 1;
    int rightCount = right - mid;

    int L[leftCount], R[rightCount];
    for (i = 0; i < leftCount; i++)
        L[i] = arr[left+i];
    for (j = 0; j < rightCount; j++)
        R[j] = arr[mid+j+1];

    i = j = 0;
    k = left;
    while(i < leftCount && j < rightCount) {
        if (L[i] <= R[j])
            arr[k++] = L[i++];
        else
            arr[k++] = R[j++];
    }

    while(i < leftCount)
        arr[k++] = L[i++];

    while(j < rightCount)
        arr[k++] = R[j++];
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
