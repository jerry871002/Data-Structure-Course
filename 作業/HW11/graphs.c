#include <stdlib.h>
#include <stdio.h>
#include "graphs.h"

GRAPH* graphCreate(int (*compare)(void* argu1, void* argu2));
GRAPH* graphDestroy(GRAPH* graph);

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
int graphInsArc(GRAPH* graph, void* pFromKey, void* pToKey) {
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
    while(fromVertexPtr && (graph->compare(fromKey, fromVertexPtr->dataPtr) > 0))
        fromVertexPtr = fromVertexPtr->pNextVertex;

    if(!fromVertexPtr || (graph->compare(fromKey, fromVertexPtr->dataPtr) != 0))
        return -2;

    // Locate destination verttex
    if(fromVertexPtr->pArc)
        return -3;

    preArcPtr = NULL;
    arcWalkPtr = fromVertexPtr->pArc;

    while(arcWalkPtr && (graph->compare(toKey, arcWalkPtr->destination->dataPtr) > 0)) {
        preArcPtr = arcWalkPtr;
        arcWalkPtr = arcWalkPtr->pNextArc;
    }

    if(!arcWalkPtr || (graph->compare(toKey, arcWalkPtr->destination->dataPtr) > 0))
        return -3;

    toVertexPtr = arcWalkPtr = destination;

    //from, toVertex & arcPtr located. Delete arc
    (fromVertexPtr->outDegree)--;
    (toVertex->inDegree)--;
    if(!preArcPtr)
        // Deleting first arc
        fromVertexPtr->pArc = arcWalkPtr->pNextArc;
    else
        preArcPtr->pNextArc = arcWalkPtr->pNextArc;
    free(arcWalkPtr);
    return 1;
}

int graphRetrVrtx(GRAPH* graph, void* pKey, void** pDataOut);
int graphFrstArc(GRAPH* graph, void* pKey, void** pDataOut);

/*
    Processed Flag: 0 = not processed
                    1 = pushed into stack
                    2 = processed
*/
void graphDpthFrst(GRAPH* graph, void (*process)(void* dataPtr)) {
    bool success;
    VERTEX* wlakPtr;
    VERTEX* vertexPtr;
    VERTEX* vertToPtr;
    STACK* stack;
    ARC* arcWalkPtr;
}

void graphBrdthFrst(GRAPH* graph, void (*process)(void* dataPtr));

bool graphEmpty(GRAPH* graph);
bool graphFull(GRAPH* graph);
int graphCount(GRAPH* graph);
