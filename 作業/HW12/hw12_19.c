#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX 1000
#define SWAP(x, y) {int t; t = x; x = y; y = t; swapCount++;}

int partition(int sortData[], int left, int right);
void quickSort(int sortData[], int left, int right);

int swapCount = 0;

int main() {
    srand(time(NULL));

    int numbers[MAX] = {0};

    printf("Before sorting: ");
    for(int i = 0; i < MAX; i++) {
        numbers[i] = rand() % MAX;
        printf("%d ", numbers[i]);
    }

    quickSort(numbers, 0, MAX-1);

    printf("\n\nAfter sorting: ");
    for(int i = 0; i < MAX; i++)
        printf("%d ", numbers[i]);

    printf("\n\nTotal swaps: %d\n", swapCount);

    return 0;
}

int partition(int sortData[], int left, int right) {
    int pivot = sortData[right];
    int i = left - 1;
    for(int j = left; j < right; j++) {
        if(sortData[j] <= pivot) {
            i++;
            SWAP(sortData[i], sortData[j]);
        }
    }

    SWAP(sortData[i+1], sortData[right]);
    return i + 1;
}

void quickSort(int sortData[], int left, int right) {
    if(left < right) {
        int pivot = partition(sortData, left, right);
        quickSort(sortData, left, pivot - 1);
        quickSort(sortData, pivot + 1, right);
    }
}
