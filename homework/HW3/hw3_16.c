// Usage: <executable> testdata.txt

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

int main(int argc, char const *argv[]) {
    FILE* inFile = fopen(argv[1], "r");

    STACK* stack;
    stack = createStack();

    int data;
    while(fscanf(inFile, "%d", &data) != EOF) {
        int* dataPtr = (int*)malloc(sizeof(int));
        *dataPtr = data;
        if(data >= 0)
            pushStack(stack, dataPtr);
        else {
            if(stackCount(stack) < 5) {
                printf("The stack has less than 5 items.\n");
                return 1;
            } else {
                for(int i = 0; i < 5; i++) {
                    data = *((int*)popStack(stack));
                    printf("%d ", data);
                }
            }
        }
    }

    printf("\nThe remaining items are: ");
    while(stackCount(stack) != 0) {
        data = *((int*)popStack(stack));
        printf("%d ", data);
    }
    printf("\n");

    destroyStack(stack);

    return 0;
}
