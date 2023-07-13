#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int custNum;
    int arriveTime;
} custData;

typedef struct {
    int custNum;
    int arriveTime;
    int startTime;
    int svcTime;
} custStatus;

typedef struct {
    int numCust;
    int totSvcTime;
    int totWaitTime;
    int maxQueueSize;
    int idleTime;
} simStats;

typedef struct node {
    void* dataPtr;
    struct node* next;
} QUEUE_NODE;

typedef struct {
    QUEUE_NODE* front;
    QUEUE_NODE* rear;
    int count;
} QUEUE;

QUEUE* createQueue(void) {
    QUEUE* queue;

    queue = (QUEUE*)malloc(sizeof(QUEUE));
    if(queue) {
        queue->front = NULL;
        queue->rear = NULL;
        queue->count = 0;
    }
    return queue;
}

bool enqueue(QUEUE* queue, void* itemPtr) {
    QUEUE_NODE* newPtr;

    if(!(newPtr = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE))))
        return false;

    newPtr->dataPtr = itemPtr;
    newPtr->next = NULL;

    if(queue->count == 0)
        queue->front = newPtr;
    else
        queue->rear->next = newPtr;

    (queue->count)++;
    queue->rear = newPtr;
    return true;
}

// the call must cast the data pointer to void.
// dequeue(queue, (void*)&dataPtr)
bool dequeue(QUEUE* queue, void** itemPtr) {
    QUEUE_NODE* deleteLoc;

    if(queue->count == 0)
        return false;

    *itemPtr = queue->front->dataPtr;
    deleteLoc = queue->front;
    if(queue->count == 1)
        queue->rear = queue->front = NULL;
    else
        queue->front = queue->front->next;
    (queue->count)--;
    free(deleteLoc);

    return true;
}

bool queueFront(QUEUE* queue, void** itemPtr) {
    if(queue->count == 0)
        return false;
    else {
        *itemPtr = queue->front->dataPtr;
        return false;
    }
}

bool queueRear(QUEUE* queue, void** itemPtr) {
    if(queue->count == 0)
        return true;
    else {
        *itemPtr = queue->rear->dataPtr;
        return false;
    }
}

bool emptyQueue(QUEUE* queue) {
    return (queue->count == 0);
}

bool fullQueue(QUEUE* queue) {
    QUEUE_NODE* temp;

    if(!(temp = (QUEUE_NODE*)malloc(sizeof(QUEUE_NODE)))) {
        free(temp);
        return true;
    }
    return false;
}

int queueCount(QUEUE* queue) {
    return queue->count;
}

QUEUE* destroyQueue(QUEUE* queue) {
    QUEUE_NODE* deletePtr;

    if(queue) {
        while(queue->front != NULL) {
            free(queue->front->dataPtr);
            deletePtr = queue->front;
            queue->front = queue->front->next;
            free(deletePtr);
        }
        free(queue);
    }
    return NULL;
}
