#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "graphs.h"

int compare(char* argu1, char* argu2);
void spanningTree(GRAPH* graph);

int main() {
    // For traversing the graph
    VERTEX* vertexPtr;
    ARC* arcWalkPtr;

    FILE* inFile = fopen("inGraph.txt", "r");

    GRAPH* graph = graphCreate(&compare);

    // Insert vertices
    while(1) {
        char* data = (char*)malloc(sizeof(char));
        fscanf(inFile, " %c", data);
        if(*data == '.') {
            free(data);
            break;
        }
        graphInsVrtx(graph, data);
    }

    // Insert arc
    while(1) {
        char dataFrom;
        char dataTo;
        int weight;
        if(fscanf(inFile, " %c %c %d", &dataFrom, &dataTo, &weight) != EOF)
            graphInsArc(graph, &dataFrom, &dataTo, weight);
        else
            break;
    }

    fclose(inFile);

    printf("Show original tree:\n");
    vertexPtr = graph->first;
    while(vertexPtr) {
        printf("(%c)", *((char*)(vertexPtr->dataPtr)));

        arcWalkPtr = vertexPtr->pArc;
        while(arcWalkPtr) {
            printf(" <-> (%c, %d)", *((char*)(arcWalkPtr->destination->dataPtr)), arcWalkPtr->weight);
            arcWalkPtr = arcWalkPtr->pNextArc;
        }

        vertexPtr = vertexPtr->pNextVertex;
        printf("\n");
    }

    spanningTree(graph);
    printf("Show minimun spanning tree:\n");
    vertexPtr = graph->first;
    while(vertexPtr) {
        printf("(%c)", *((char*)(vertexPtr->dataPtr)));

        arcWalkPtr = vertexPtr->pArc;
        while(arcWalkPtr) {
            if(arcWalkPtr->inTree)
                printf(" <-> (%c, %d)", *((char*)(arcWalkPtr->destination->dataPtr)), arcWalkPtr->weight);
            arcWalkPtr = arcWalkPtr->pNextArc;
        }

        vertexPtr = vertexPtr->pNextVertex;
        printf("\n");
    }
    return 0;
}

int compare(char* argu1, char* argu2) {
    return *argu1 - *argu2;
}

void spanningTree(GRAPH* graph) {
    VERTEX* vertexPtr;
    ARC* arcWalkPtr;
    ARC* minEdgeLoc;
    bool treeComplete;
    int minEdge;

    if(!graph->first)
        return;

    // Set all inTree to false
    vertexPtr = graph->first;
    while(vertexPtr) {
        vertexPtr->inTree = false;

        arcWalkPtr = vertexPtr->pArc;
        while(arcWalkPtr) {
            arcWalkPtr->inTree = false;
            arcWalkPtr = arcWalkPtr->pNextArc;
        }

        vertexPtr = vertexPtr->pNextVertex;
    }

    graph->first->inTree = true;
    treeComplete = false;
    while(!treeComplete) {
        treeComplete = true;
        minEdge = INT_MAX;
        minEdgeLoc = NULL;

        vertexPtr = graph->first;
        while(vertexPtr) {
            if(vertexPtr->inTree && vertexPtr->outDegree > 0) {
                arcWalkPtr = vertexPtr->pArc;
                while(arcWalkPtr) {
                    if(!(arcWalkPtr->destination->inTree)) {
                        treeComplete = false;
                        if(arcWalkPtr->weight < minEdge) {
                            minEdge = arcWalkPtr->weight;
                            minEdgeLoc = arcWalkPtr;
                        }
                    }
                    arcWalkPtr = arcWalkPtr->pNextArc;
                }
            }
            vertexPtr = vertexPtr->pNextVertex;
        }

        if(minEdgeLoc) {
            minEdgeLoc->inTree = true;
            minEdgeLoc->destination->inTree = true;
        }
    }
}
