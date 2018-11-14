#include <stdbool.h>
#include <stdlib.h>

typedef struct node {
    void* dataPtr;
    struct node* link;
} NODE;

typedef struct {
    int count;
    NODE* pos;
    NODE* head;
    NODE* rear;
    int (*compare)(void* argu1, void* argu2);
} LIST;

LIST* createList(int (*compare)(void* argu1, void* argu2));
LIST* destroyList(LIST* list);
int addNode(LIST* pList, void* dataInPtr);
bool removeNode(LIST* pList, void* keyPtr, void** dataOutPtr);
bool searchList(LIST* pList, void* pArgu, void** pDataOut);
bool retrieveNode(LIST* pList, void* pArgu, void** dataOutPtr);
bool traverse(LIST* pList, int fromWhere, void** dataOutPtr);

int listCount(LIST* pList);
bool emptyList(LIST* pList);
bool fullList(LIST* pList);

// access to static functions is restricted to the file where they are declared
static bool _insert(LIST* pList, NODE* pPre, void* dataInPtr);
static void _delete(LIST* pList, NODE* pPre, NODE* pLoc, void** dataOutPtr);
static bool _search(LIST* pList, NODE** pPre, NODE** pLoc, void* pArgu);

LIST* createList(int (*compare)(void* argu1, void* argu2)) {
    LIST* list = (LIST*)malloc(sizeof(LIST));
    if(list) {
        list->head = NULL;
        list->pos = NULL;
        list->rear = NULL;
        list->count = 0;
        list->compare = compare;
    }
    return list;
}

LIST* destroyList(LIST* pList) {
    NODE* deletePtr;

    if(pList) {
        while(pList->count >0) {
            free(pList->head->dataPtr);

            deletePtr = pList->head;
            pList->head = pList->head->link;
            (pList->count)--;
            free(deletePtr);
        }
        free(pList);
    }
    return NULL;
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

bool removeNode(LIST* pList, void* keyPtr, void** dataOutPtr) {
    bool found;

    NODE* pPre;
    NODE* pLoc;

    found = _search(pList, &pPre, &pLoc, keyPtr);
    if(found)
        _delete(pList, pPre, pLoc, dataOutPtr);

    return found;
}

bool searchList(LIST* pList, void* pArgu, void** pDataOut) {
    bool found;

    NODE* pPre;
    NODE* pLoc;

    found = _search(pList, &pPre, &pLoc, pArgu);
    if(found)
        *pDataOut = pLoc->dataPtr;
    else
        *pDataOut = NULL;
    return found;
}

bool retrieveNode(LIST* pList, void* pArgu, void** dataOutPtr) {
    bool found;

    NODE* pPre;
    NODE* pLoc;

    found = _search(pList, &pPre, &pLoc, pArgu);
    if(found) {
        *dataOutPtr = pLoc->dataPtr;
        return true;
    }

    *dataOutPtr = NULL;
    return false;
}

bool traverse(LIST* pList, int fromWhere, void** dataOutPtr) {
    if(pList->count == 0)
        return false;

    if(fromWhere == 0) {
        // start from first node
        pList->pos = pList->head;
        *dataOutPtr = pList->pos->dataPtr;
        return true;
    } else {
        // start from current position
        if(pList->pos->link == NULL)
            return false;
        else {
            pList->pos = pList->pos->link;
            *dataOutPtr = pList->pos->dataPtr;
            return true;
        }
    }
}

int listCount(LIST* pList) {
    return pList->count;
}

bool emptyList(LIST* pList) {
    return (pList->count == 0);
}

bool fullList(LIST* pList) {
    NODE* temp;

    if((temp = (NODE*)malloc(sizeof(NODE)))) {
        free(temp);
        return false;
    }

    return true;
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



static void _delete(LIST* pList, NODE* pPre, NODE* pLoc, void** dataOutPtr) {
    *dataOutPtr = pLoc->dataPtr;
    if(pPre == NULL)
        // deleting first node
        pList->head = pLoc->link;
    else
        // deleting any other node
        pPre->link = pLoc->link;

    if(pLoc->link == NULL)
        // set rear when deleting last node
        pList->rear = pPre;

    (pList->count)--;
    free(pLoc);
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
