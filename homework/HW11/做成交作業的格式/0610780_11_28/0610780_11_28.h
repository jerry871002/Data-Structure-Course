#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int count;
    struct vertex* first;
    int (*compare)(void* argu1, void* argu2);
} GRAPH;

typedef struct vertex {
    struct vertex* pNextVertex;
    void* dataPtr;
    int inDegree;
    int outDegree;
    struct arc* pArc;
    bool inTree;
    int pathLength;
    struct vertex* preVertex;
} VERTEX;

typedef struct arc {
    struct vertex* destination;
    struct arc* pNextArc;
    bool inTree;
    int weight;
} ARC;

typedef struct stackNode {
    void* dataPtr;
    struct stackNode* link;
} STACK_NODE;

typedef struct {
    int count;
    STACK_NODE* top;
} STACK;

GRAPH* graphCreate(int (*compare)(void* argu1, void* argu2));
void graphInsVrtx(GRAPH* graph, void* dataInPtr);
int graphInsArc(GRAPH* graph, void* pFromKey, void* pToKey, int weight);

STACK* createStack(void);
bool pushStack(STACK* stack, void* dataInPtr);
void* popStack(STACK* stack);
bool emptyStack(STACK* stack);

GRAPH* graphCreate(int (*compare)(void* argu1, void* argu2)) {
    GRAPH* graph;
    graph = (GRAPH*)malloc(sizeof(GRAPH));
    if(graph) {
        graph->count = 0;
        graph->first = NULL;
        graph->compare = compare;
    }
    return graph;
}

// Graph Insert Vertex
void graphInsVrtx(GRAPH* graph, void* dataInPtr) {
    VERTEX* newPtr;
    VERTEX* locPtr;
    VERTEX* predPtr;

    newPtr = (VERTEX*)malloc(sizeof(VERTEX));
    if(newPtr) {
        newPtr->pNextVertex = NULL;
        newPtr->dataPtr = dataInPtr;
        newPtr->inDegree = 0;
        newPtr->outDegree = 0;
        newPtr->pArc = NULL;
        (graph->count)++;
    } else {
        printf("Overflow error 100\a\n");
        exit(100);
    }

    // Find insertion point
    locPtr = graph->first;
    if(!locPtr)
        // Empty graph. Insert at beginning
        graph->first = newPtr;
    else {
        predPtr = NULL;
        while(locPtr && (graph->compare(dataInPtr, locPtr->dataPtr) > 0)) {
            predPtr = locPtr;
            locPtr = locPtr->pNextVertex;
        }
        if(!predPtr)
            // Insert before first vertex
            graph->first = newPtr;
        else
            predPtr->pNextVertex = newPtr;

        newPtr->pNextVertex = locPtr;
    }
}

/*
    return  +1 if successful
            -1 if memory overflow
            -2 if fromKey not found
            -3 if toKey not found
*/
int graphInsArc(GRAPH* graph, void* pFromKey, void* pToKey, int weight) {
    ARC* newPtr;
    ARC* arcPredPtr;
    ARC* arcWalkPtr;
    VERTEX* vertFromPtr;
    VERTEX* vertToPtr;

    newPtr = (ARC*)malloc(sizeof(ARC));
    if(!newPtr)
        return -1;

    // Locate source vertex
    vertFromPtr = graph->first;
    while(vertFromPtr && (graph->compare(pFromKey, vertFromPtr->dataPtr) > 0))
        vertFromPtr = vertFromPtr->pNextVertex;

    if(!vertFromPtr || (graph->compare(pFromKey, vertFromPtr->dataPtr) != 0))
        return -2;

    // Locate to vertex
    vertToPtr = graph->first;
    while(vertToPtr && (graph->compare(pToKey, vertToPtr->dataPtr) > 0))
        vertToPtr = vertToPtr->pNextVertex;

    if(!vertToPtr || (graph->compare(pToKey, vertToPtr->dataPtr) != 0))
        return -3;

    // From and to vertices located. Insert new arc
    (vertFromPtr->outDegree)++;
    (vertToPtr->inDegree)++;
    newPtr->destination = vertToPtr;
    if(!vertFromPtr->pArc) {
        // Inserting first arc for this vertex
        vertFromPtr->pArc = newPtr;
        newPtr->pNextArc = NULL;
        newPtr->weight = weight;
        return 1;
    }
    // Find insertion point in adjacency (arc) list
    arcPredPtr = NULL;
    arcWalkPtr = vertFromPtr->pArc;
    while(arcWalkPtr && (graph->compare(pToKey, arcWalkPtr->destination->dataPtr)) >= 0) {
        arcPredPtr = arcWalkPtr;
        arcWalkPtr = arcWalkPtr->pNextArc;
    }

    if(!arcPredPtr)
        //Insertion before first arc
        vertFromPtr->pArc = newPtr;
    else
        arcPredPtr->pNextArc = newPtr;

    newPtr->pNextArc = arcWalkPtr;
    newPtr->weight = weight;
    return 1;
}

STACK* createStack(void) {
    STACK* stack;
    stack = (STACK*)malloc(sizeof(STACK));
    if(stack) {
        stack->count = 0;
        stack->top = NULL;
    }
    return stack;
}

bool pushStack(STACK* stack, void* dataInPtr) {
    STACK_NODE* newPtr;
    newPtr = (STACK_NODE*)malloc(sizeof(STACK_NODE));
    if(!newPtr)
        return false;

    newPtr->dataPtr = dataInPtr;

    newPtr->link = stack->top;
    stack->top = newPtr;

    (stack->count)++;
    return true;
}

void* popStack(STACK* stack) {
    void* dataOutPtr;
    STACK_NODE* temp;

    if(stack->count == 0)
        dataOutPtr = NULL;
    else {
        temp = stack->top;
        dataOutPtr = stack->top->dataPtr;
        stack->top = stack->top->link;
        free(temp);
        (stack->count)--;
    }
    return dataOutPtr;
}

bool emptyStack(STACK* stack) {
    return (stack->count == 0);
}
