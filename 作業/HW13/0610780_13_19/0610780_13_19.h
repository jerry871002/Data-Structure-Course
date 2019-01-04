#include <stdbool.h>
#include <stdlib.h>

typedef struct node {
    void* dataPtr;
    struct node* link;
} NODE;

typedef struct {
    int count;
    NODE* head;
    NODE* rear;
    int (*compare)(void* argu1, void* argu2);
} LIST;

LIST* createList(int (*compare)(void* argu1, void* argu2));
int addNode(LIST* pList, void* dataInPtr);

bool emptyList(LIST* pList);

// access to static functions is restricted to the file where they are declared
static bool _insert(LIST* pList, NODE* pPre, void* dataInPtr);
static bool _search(LIST* pList, NODE** pPre, NODE** pLoc, void* pArgu);

LIST* createList(int (*compare)(void* argu1, void* argu2)) {
    LIST* list = (LIST*)malloc(sizeof(LIST));
    if(list) {
        list->head = NULL;
        list->rear = NULL;
        list->count = 0;
        list->compare = compare;
    }
    return list;
}

int addNode(LIST* pList, void* dataInPtr) {
    bool found;
    bool success;

    NODE* pPre;
    NODE* pLoc;

    found = _search(pList, &pPre, &pLoc, dataInPtr);
    if(found)
        // Duplicate keys not allowed
        return 1;

    success = _insert(pList, pPre, dataInPtr);
    if(!success)
        // Overflow
        return -1;
    return 0;
}

bool emptyList(LIST* pList) {
    return (pList->count == 0);
}

static bool _insert(LIST* pList, NODE* pPre, void* dataInPtr) {
    NODE* pNew;

    if(!(pNew = (NODE*)malloc(sizeof(NODE))))
        return false;

    pNew->dataPtr = dataInPtr;
    pNew->link = NULL;

    if(pPre == NULL) {
        // adding before first node or to empty list
        pNew->link = pList->head;
        pList->head = pNew;
        if(pList->count == 0)
            // set rear when list empty
            pList->rear = pNew;
    } else {
        // adding in middle or at end
        pNew->link = pPre->link;
        pPre->link = pNew;
        if(pNew->link == NULL)
            // set rear when adding at end
            pList->rear = pNew;
    }

    (pList->count)++;
    return true;
}

static bool _search(LIST* pList, NODE** pPre, NODE** pLoc, void* pArgu) {
    #define COMPARE (pList->compare(pArgu, (*pLoc)->dataPtr))
    #define COMPARE_LAST (pList->compare(pArgu, pList->rear->dataPtr))

    int result;

    *pPre = NULL;
    *pLoc = pList->head;
    if(pList->count == 0)
        return false;

    if(COMPARE_LAST > 0) {
        *pPre = pList->rear;
        *pLoc = NULL;
        return false;
    }

    while ((result = COMPARE) > 0) {
        *pPre  = *pLoc;
        *pLoc = (*pLoc)->link;
    }

    if(result == 0)
        return true;
    else
        return false;
}
