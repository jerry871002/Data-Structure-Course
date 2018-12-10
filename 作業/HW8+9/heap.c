#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "heap.h"

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

//int heapCount(HEAP* heap);
//bool heapFull(HEAP* heap);
//bool heapEmpty(HEAP* heap);
//void heapDestroy(HEAP* heap);

static void _reheapUp(HEAP* heap, int childLoc) {
    int parent;
    void** heapAry;
    void* hold;

    if(childLoc) {
        heapAry = heap->heapAry;
        parent = (childLoc - 1) / 2;
        if(heap->compare(heapAry[childLoc], heapAry[parent]) > 0) {
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
            hold = heap->heapAry[root];
            heap->heapAry[root] = heap->heapAry[largeLoc];
            heap->heapAry[largeLoc] = hold;
            _reheapDown(heap, largeLoc);
        }
    }
}
