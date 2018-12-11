#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

typedef struct {
   void** heapAry;
   int last;
   int size;
   int (*compare)(void* argu1, void* argu2);
   int maxSize;
} HEAP;

HEAP* heapCreate(int maxSize, int (*compare)(void* arg1, void* arg2));
bool heapInsert(HEAP* heap, void* dataPtr);
bool heapDelete(HEAP* heap, void** dataOutPtr);

static void _reheapUp(HEAP* heap, int childLoc);
static void _reheapDown(HEAP* heap, int root);

int compare(int* argu1, int* argu2);

int count;

int main(int argc, char const *argv[]) {
    printf("Array Size\tReheap up\tReheap down\t    O(n)\tO(log(n!))\n");

    srand(time(NULL));
    int size[5] = {100, 200, 500, 1000, 2000};
    for(int i = 0; i < 5; i++) {
        HEAP* heap = heapCreate(size[i], &compare);

        count = 0;
        for(int j = 0; j < size[i]; j++) {
            int* num = (int*)malloc(sizeof(int));
            *num = rand();
            heapInsert(heap, num);
        }

        printf("%10d\t%9d\t", size[i], count);

        count = 0;
        int* outNum;
        for(int j = 0; j < size[i]; j++)
            heapDelete(heap, &outNum);

        printf("%11d\t%8d\t", count, size[i]);

        double complexity = 0;
        for(double j = 1; j <= size[i]; j++)
            complexity += log2(j);

        printf("%10.0lf\n", complexity);
    }
    return 0;
}

int compare(int* argu1, int* argu2) {
    if(!argu1) {
        if(!argu2)
            return 0;
        else
            return (-1) * (*argu2);
    } else if(!argu2)
        return (*argu1);
    else
        return *argu1 - *argu2;
}

HEAP* heapCreate(int maxSize, int (*compare)(void* arg1, void* arg2)) {
    HEAP* heap;
    heap = (HEAP*)malloc(sizeof(HEAP));
    if(!heap)
        return NULL;

    heap->last = -1;
    heap->size = 0;
    heap->compare = compare;

    // Force heap size to power of 2 -1
    heap->maxSize = (int)pow(2, ceil(log2(maxSize))) - 1;
    heap->heapAry = (void*)calloc(heap->maxSize, sizeof(void*));

    return heap;
}

bool heapInsert(HEAP* heap, void* dataPtr) {
    if(heap->size == 0) {
        heap->size = 1;
        heap->last = 0;
        heap->heapAry[heap->last] = dataPtr;
        return true;
    }

    if(heap->last == heap->maxSize - 1)
        return false;

    ++(heap->last);
    ++(heap->size);
    heap->heapAry[heap->last] = dataPtr;
    _reheapUp(heap, heap->last);
    return true;
}

bool heapDelete(HEAP* heap, void** dataOutPtr) {
    if(heap->size == 0)
        return false;

    *dataOutPtr = heap->heapAry[0];
    heap->heapAry[0] = heap->heapAry[heap->last];
    (heap->last)--;
    (heap->size)--;
    _reheapDown(heap, 0);
    return true;
}

static void _reheapUp(HEAP* heap, int childLoc) {
    int parent;
    void** heapAry;
    void* hold;

    if(childLoc) {
        heapAry = heap->heapAry;
        parent = (childLoc - 1) / 2;
        if(heap->compare(heapAry[childLoc], heapAry[parent]) > 0) {
            count++;
            hold = heapAry[parent];
            heapAry[parent] = heapAry[childLoc];
            heapAry[childLoc] = hold;
            _reheapUp(heap, parent);
        }
    }
}

static void _reheapDown(HEAP* heap, int root) {
    void* hold;
    void* leftData;
    void* rightData;
    int largeLoc;
    int last;

    last = heap->last;
    if((root * 2 + 1) <= last) { // left subtree
        // There is at least one child
        leftData = heap->heapAry[root * 2 + 1];
        if((root * 2 + 2) <= last)
            rightData = heap->heapAry[root * 2 + 2];
        else
            rightData = NULL;

        // Determine which child is larger
        if((!rightData) || heap->compare(leftData, rightData) > 0)
            // if no right key or leftKey greater
            largeLoc = root * 2 + 1;
        else
            largeLoc = root * 2 + 2;

        if(heap->compare(heap->heapAry[root], heap->heapAry[largeLoc] < 0)) {
            // parent < children
            count++;
            hold = heap->heapAry[root];
            heap->heapAry[root] = heap->heapAry[largeLoc];
            heap->heapAry[largeLoc] = hold;
            _reheapDown(heap, largeLoc);
        }
    }
}
