#include <stdio.h>
#include <stdlib.h>
#include "list.h"

#define TABLE_SIZE 4

typedef struct {
    int partNum;
    int quantity;
} INVENTORY;

int compare(void* argu1, void* argu2);

int main() {
    LIST* hashList[TABLE_SIZE];
    for(int i = 0; i < TABLE_SIZE; i++)
        hashList[i] = createList(&compare);

    FILE* inFile = fopen("inventory.txt", "r");

    int partNum, quantity;
    while(fscanf("%d %d", &partNum, &quantity) != EOF) {
        INVENTORY* newPart = (INVENTORY*)malloc(sizeof(INVENTORY));
    }
    return 0;
}

int compare(void* argu1, void* argu2) {
    return 1;
}
