#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "0610780_11_28.h"

int compare(char* argu1, char* argu2);
bool shortestPath(GRAPH* graph, void* startKey);

int main() {
    VERTEX* vertexPtr;
    ARC* arcWalkPtr;

    FILE* inFile = fopen("silicon_map.txt", "r");

    GRAPH* graph = graphCreate(&compare);

    // Insert vertices
    while(1) {
        char* data = (char*)malloc(sizeof(char) * 20);
        fscanf(inFile, "%s", data);
        if(strcmp(data, ".") == 0) {
            free(data);
            break;
        }
        graphInsVrtx(graph, data);
    }

    // Insert arc
    while(1) {
        char dataFrom[20];
        char dataTo[20];
        int weight;
        if(fscanf(inFile, "%s %s %d", dataFrom, dataTo, &weight) != EOF)
            graphInsArc(graph, dataFrom, dataTo, weight);
        else
            break;
    }

    fclose(inFile);

    char start[20];
    while(1) {
        printf("Please enter a location to start: ");
        scanf("%s", start);

        if(shortestPath(graph, &start))
            break;
    }

    bool found = false;
    char des[20];
    while(1) {
        printf("Please enter your destination: ");
        scanf("%s", &des);

        vertexPtr = graph->first;
        while(vertexPtr) {
            if(graph->compare(&des, vertexPtr->dataPtr) == 0) {
                found = true;
                break;
            }
            vertexPtr = vertexPtr->pNextVertex;
        }

        if(found)
            break;
        else
            printf("Destination not found.\n");
    }

    printf("\n=====The shortest route from %s to %s is=====\n", start, des);

    STACK* pathStack = createStack();
    while(vertexPtr) {
        pushStack(pathStack, vertexPtr->dataPtr);
        vertexPtr = vertexPtr->preVertex;
    }

    while(!emptyStack(pathStack))
        printf("%s\n", ((char*)popStack(pathStack)));
    printf("\n");

    return 0;
}

int compare(char* argu1, char* argu2) {
    return strcmp(argu1, argu2);
}

bool shortestPath(GRAPH* graph, void* startKey) {
    VERTEX* vertexPtr;
    VERTEX* vertexStart;
    VERTEX* preVertex;
    ARC* arcWalkPtr;
    ARC* minEdgeLoc;
    ARC* pathLoc;
    ARC* edgeLoc;
    bool found;
    bool treeComplete;
    int newPathLen;
    int minEdge;
    int minPath;

    if(graph->count == 0)
        return false;

    // Set all inTree to false, pathLength to maximum integer
    vertexPtr = graph->first;
    while(vertexPtr) {
        vertexPtr->inTree = false;
        vertexPtr->pathLength = 1000; // 1000 instead of INT_MAX, prevent overflow
        vertexPtr->preVertex = NULL;

        arcWalkPtr = vertexPtr->pArc;
        while(arcWalkPtr) {
            arcWalkPtr->inTree = false;
            arcWalkPtr = arcWalkPtr->pNextArc;
        }

        vertexPtr = vertexPtr->pNextVertex;
    }

    // Find start position
    found = false;
    vertexStart = NULL;
    vertexPtr = graph->first;
    while(vertexPtr) {
        if(graph->compare(startKey, vertexPtr->dataPtr) == 0) {
            found = true;
            break;
        }
        vertexPtr = vertexPtr->pNextVertex;
    }
    if(!found) {
        printf("Start position not found.\n");
        return false;
    }
    else
        vertexStart = vertexPtr;

    // Derive minimum path tree
    vertexStart->inTree = true;
    vertexStart->pathLength = 0;
    treeComplete = false;
    while(!treeComplete) {
        treeComplete = true;
        minEdgeLoc = NULL;
        pathLoc = NULL;
        newPathLen = 1000; // 1000 instead of INT_MAX, prevent overflow

        vertexPtr = vertexStart;
        for(int i = 0; i < graph->count; i++) {
            // Walk through graph checking vertices in tree
            if(vertexPtr->inTree && (vertexPtr->outDegree > 0)) {
                edgeLoc = vertexPtr->pArc;
                minPath = vertexPtr->pathLength;
                minEdge = 1000; // 1000 instead of INT_MAX, prevent overflow

                while(edgeLoc) {
                    // Locate smallest path from this vertex
                    if(!(edgeLoc->destination->inTree)) {
                        treeComplete = false;
                        if(edgeLoc->weight < minEdge) {
                            minEdge = edgeLoc->weight;
                            minEdgeLoc = edgeLoc;
                        }
                    }
                    edgeLoc = edgeLoc->pNextArc;
                }
                // Test for shortest path
                if(minPath + minEdge < newPathLen) {
                    newPathLen = minPath + minEdge;
                    pathLoc = minEdgeLoc;
                    preVertex = vertexPtr;
                }
            }

            // Get next vertex
            if(vertexPtr->pNextVertex)
                vertexPtr = vertexPtr->pNextVertex;
            else
                vertexPtr = graph->first;
        }
        if(pathLoc) {
            pathLoc->inTree = true;
            pathLoc->destination->inTree = true;
            pathLoc->destination->pathLength = newPathLen;
            pathLoc->destination->preVertex = preVertex;
        }
    }
    return true;
}
