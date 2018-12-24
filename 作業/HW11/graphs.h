#include <stdbool.h>

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
    short processed; // Not used in HW11
    struct arc* pArc;
    bool inTree; // 11_22 11_28
    int pathLength; // 11_28
    struct vertex* preVertex; // 11_28
} VERTEX;

typedef struct arc {
    struct vertex* destination;
    struct arc* pNextArc;
    bool inTree; // 11_22 11_28
    int weight; // 11_22 11_28
} ARC;

GRAPH* graphCreate(int (*compare)(void* argu1, void* argu2));
//GRAPH* graphDestroy(GRAPH* graph);

void graphInsVrtx(GRAPH* graph, void* dataInPtr);
int graphDltVrtx(GRAPH* graph, void* dltKey);
int graphInsArc(GRAPH* graph, void* pFromKey, void* pToKey, int weight);
int graphDltArc(GRAPH* graph, void* pFromKey, void* pToKey);
//int graphRetrVrtx(GRAPH* graph, void* pKey, void** pDataOut);
//int graphFrstArc(GRAPH* graph, void* pKey, void** pDataOut);

void graphDpthFrst(GRAPH* graph, void (*process)(void* dataPtr));
void graphBrdthFrst(GRAPH* graph, void (*process)(void* dataPtr));

//bool graphEmpty(GRAPH* graph);
//bool graphFull(GRAPH* graph);
//int graphCount(GRAPH* graph);
