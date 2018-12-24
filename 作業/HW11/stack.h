#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct stackNode {
    void* dataPtr;
    struct stackNode* link;
} STACK_NODE;

typedef struct {
    int count;
    STACK_NODE* top;
} STACK;

STACK* createStack(void);
bool pushStack(STACK* stack, void* dataInPtr);
void* popStack(STACK* stack);
void* stackTop(STACK* stack);
bool emptyStack(STACK* stack);
bool fullStack(STACK* stack);
int stackCount(STACK* stack);
STACK* destroyStack(STACK* stack);

#endif
