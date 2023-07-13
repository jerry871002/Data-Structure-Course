#include <stdlib.h>
#include <stdio.h>
#include "graphs.h"
#include "stack.h"
#include "queue.h"

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

//GRAPH* graphDestroy(GRAPH* graph);

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
        newPtr->processed = 0;
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
            -1 if degree not zero
            -2 if dltKey not found
*/
int graphDltVrtx(GRAPH* graph, void* dltKey) {
    VERTEX* predPtr;
    VERTEX* walkPtr;

    if(!graph->first)
        return -2;

    // Locate vertex to be deleted
    predPtr = NULL;
    walkPtr = graph->first;
    while(walkPtr && (graph->compare(dltKey, walkPtr->dataPtr) > 0)) {
        predPtr = walkPtr;
        walkPtr = walkPtr->pNextVertex;
    }
    if(!walkPtr || (graph->compare(dltKey, walkPtr->dataPtr) != 0))
        return -2;

    // Found vertex. Test degree
    if((walkPtr->inDegree > 0) || (walkPtr->outDegree > 0))
        return -1;

    // OK to delete
    if(!predPtr)
        // Delete the first vertex
        graph->first = walkPtr->pNextVertex;
    else
        predPtr->pNextVertex = walkPtr->pNextVertex;

    --(graph->count);
    free(walkPtr);
    return 1;
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

/*
    return  +1 if successful
            -2 if fromKey not found
            -3 if toKey not found
*/
int graphDltArc(GRAPH* graph, void* pFromKey, void* pToKey) {
    VERTEX* fromVertexPtr;
    VERTEX* toVertexPtr;
    ARC* preArcPtr;
    ARC* arcWalkPtr;

    if(!graph->first)
        return -2;

    // Locate source vertex
    fromVertexPtr = graph->first;
    while(fromVertexPtr && (graph->compare(pFromKey, fromVertexPtr->dataPtr) > 0))
        fromVertexPtr = fromVertexPtr->pNextVertex;

    if(!fromVertexPtr || (graph->compare(pFromKey, fromVertexPtr->dataPtr) != 0))
        return -2;

    // Locate destination vertex
    if(fromVertexPtr->pArc)
        return -3;

    preArcPtr = NULL;
    arcWalkPtr = fromVertexPtr->pArc;

    while(arcWalkPtr && (graph->compare(pToKey, arcWalkPtr->destination->dataPtr) > 0)) {
        preArcPtr = arcWalkPtr;
        arcWalkPtr = arcWalkPtr->pNextArc;
    }

    if(!arcWalkPtr || (graph->compare(pToKey, arcWalkPtr->destination->dataPtr) > 0))
        return -3;

    toVertexPtr = arcWalkPtr->destination;

    //from, toVertex & arcPtr located. Delete arc
    (fromVertexPtr->outDegree)--;
    (toVertexPtr->inDegree)--;
    if(!preArcPtr)
        // Deleting first arc
        fromVertexPtr->pArc = arcWalkPtr->pNextArc;
    else
        preArcPtr->pNextArc = arcWalkPtr->pNextArc;
    free(arcWalkPtr);
    return 1;
}

//int graphRetrVrtx(GRAPH* graph, void* pKey, void** pDataOut);
//int graphFrstArc(GRAPH* graph, void* pKey, void** pDataOut);

/*
    Processed Flag: 0 = not processed
                    1 = pushed into stack
                    2 = processed
*/
void graphDpthFrst(GRAPH* graph, void (*process)(void* dataPtr)) {
    bool success;
    VERTEX* walkPtr;
    VERTEX* vertexPtr;
    VERTEX* vertToPtr;
    STACK* stack;
    ARC* arcWalkPtr;

    if(!graph->first)
        return;

    // Set processed flags to not processed
    walkPtr = graph->first;
    while(walkPtr) {
        walkPtr->processed = 0;
        walkPtr = walkPtr->pNextVertex;
    }

    // Process each vertex in list
    stack = createStack();
    walkPtr = graph->first;
    while(walkPtr) {
        if(walkPtr->processed == 0) {
            // Push & set flag to pushed
            success = pushStack(stack, walkPtr);
            if(!success) {
                printf("\aStack overflow\a\n");
                exit(100);
            }
            walkPtr->processed = 1;
        }

        // Process descendents of vertex at stack top
        while(!emptyStack(stack)) {
            vertexPtr = popStack(stack);
            process(vertexPtr->dataPtr);
            vertexPtr->processed = 2;

            // Push all vertices from adjacency list
            arcWalkPtr = vertexPtr->pArc;
            while(arcWalkPtr) {
                vertToPtr = arcWalkPtr->destination;
                if(vertToPtr->processed == 0) {
                    success = pushStack(stack, vertToPtr);
                    if(!success) {
                        printf("\aStack overflow\a\n");
                        exit(100);
                    }
                    vertToPtr->processed = 1;
                }
                arcWalkPtr = arcWalkPtr->pNextArc;
            }
        }
        walkPtr = walkPtr->pNextVertex;
    }
    destroyStack(stack);
}

void graphBrdthFrst(GRAPH* graph, void (*process)(void* dataPtr)) {
    bool success;
    VERTEX* walkPtr;
    VERTEX* vertexPtr;
    VERTEX* vertToPtr;
    QUEUE* queue;
    ARC* arcWalkPtr;

    if(!graph->first)
        return;

    // Set processed flags to not processed
    walkPtr = graph->first;
    while(walkPtr) {
        walkPtr->processed = 0;
        walkPtr = walkPtr->pNextVertex;
    }

    // Process each vertex in list
    queue = createQueue();
    walkPtr = graph->first;
    while(walkPtr) {
        if(walkPtr->processed == 0) {
            // Push & set flag to pushed
            success = enqueue(queue, walkPtr);
            if(!success) {
                printf("\aStack overflow\a\n");
                exit(100);
            }
            walkPtr->processed = 1;
        }

        // Process descendents of vertex at stack top
        while(!emptyQueue(queue)) {
            dequeue(queue, (void**)&vertexPtr);
            process(vertexPtr->dataPtr);
            vertexPtr->processed = 2;

            // Enqueue all vertices from adjacency list
            arcWalkPtr = vertexPtr->pArc;
            while(arcWalkPtr) {
                vertToPtr = arcWalkPtr->destination;
                if(vertToPtr->processed == 0) {
                    success = enqueue(queue, vertToPtr);
                    if(!success) {
                        printf("\aStack overflow\a\n");
                        exit(100);
                    }
                    vertToPtr->processed = 1;
                }
                arcWalkPtr = arcWalkPtr->pNextArc;
            }
        }
        walkPtr = walkPtr->pNextVertex;
    }
    destroyQueue(queue);
}

//bool graphEmpty(GRAPH* graph);
//bool graphFull(GRAPH* graph);
//int graphCount(GRAPH* graph);
