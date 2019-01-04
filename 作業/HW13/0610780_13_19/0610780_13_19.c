#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "0610780_13_19.h"

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

    int partNum, quantity, totalNode = 0;
    while(fscanf(inFile, "%d %d", &partNum, &quantity) != EOF) {
        totalNode++;

        INVENTORY* newPart = (INVENTORY*)malloc(sizeof(INVENTORY));
        newPart->partNum = partNum;
        newPart->quantity = quantity;

        addNode(hashList[partNum%TABLE_SIZE], newPart);
    }

    fclose(inFile);

    // Show all content in the hash table
    printf("Home Addr\tPrime Area\tOverflow List\n");
    for(int i = 0; i < TABLE_SIZE; i++) {
        // Print home address
        printf("%9d\t", i);

        if(!emptyList(hashList[i])) {
            // Print prime area
            printf("%5d/%-4d\t", ((INVENTORY*)(hashList[i]->head->dataPtr))->partNum, ((INVENTORY*)(hashList[i]->head->dataPtr))->quantity);

            // If there are overflow list
            if(hashList[i]->count > 1) {
                NODE* walk = hashList[i]->head->link;
                for(int j = 0; j < (hashList[i]->count) - 1; j++) {
                    printf("%d/%d ", ((INVENTORY*)(walk->dataPtr))->partNum, ((INVENTORY*)(walk->dataPtr))->quantity);
                    walk = walk->link;
                }
            }
        }
        printf("\n");
    }
    printf("\n");

    int primeCount = 0, listCount = 0, longest = 0;
    for(int i = 0; i < TABLE_SIZE; i++) {
        if(!emptyList(hashList[i])) {
            primeCount++;
            if(hashList[i]->count > 1)
                listCount ++;
            if(hashList[i]->count > longest)
                longest = hashList[i]->count;
        }
    }

    printf("Percentage of prime area filled: %5.1f %%\n", (float)primeCount/TABLE_SIZE*100);
    printf("Average nodes in linked list:    %5.1f node(s)\n", (float)(totalNode-primeCount)/listCount);
    printf("Logest linked list:              %5d node(s)\n\n", longest-1);

    int searchNum;
    printf("Please enter a part number to search: ");
    scanf("%d", &searchNum);

    bool found = false;
    for(int i = 0; i < TABLE_SIZE; i++) {
        if(!emptyList(hashList[i])) {
            NODE* walk = hashList[i]->head;
            for(int j = 0; j < hashList[i]->count; j++) {
                if(((INVENTORY*)(walk->dataPtr))->partNum == searchNum) {
                    printf("Part number \"%d\" has sold \"%d\" in the past month.\n\n", ((INVENTORY*)(walk->dataPtr))->partNum, ((INVENTORY*)(walk->dataPtr))->quantity);
                    found = true;
                    break;
                }
                walk = walk->link;
            }
        }
        if(found)
            break;
    }

    return 0;
}

int compare(void* argu1, void* argu2) {
    return 1;
}
