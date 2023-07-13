#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>

typedef struct queueNode {
    void* dataPtr;
    struct queueNode* next;
} QUEUE_NODE;

typedef struct {
    QUEUE_NODE* front;
    QUEUE_NODE* rear;
    int count;
} QUEUE;

QUEUE* createQueue(void);
QUEUE* destroyQueue(QUEUE* queue);

bool dequeue(QUEUE* queue, void** itemPtr);
bool enqueue(QUEUE* queue, void* itemPtr);
bool queueFront(QUEUE* queue, void** itemPtr);
bool queueRear(QUEUE* queue, void** itemPtr);
int queueCount(QUEUE* queue);

bool emptyQueue(QUEUE* queue);
bool fullQueue(QUEUE* queue);

#endif