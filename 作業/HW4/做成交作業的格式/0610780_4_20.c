#include "0610780_4_20.h"
#include <stdio.h>
#include <stdlib.h>

bool isNum(void* data);

int main(int argc, char const *argv[]) {
    FILE* inFile = fopen("test.txt", "r");
    QUEUE* queue = createQueue();

    char data;
    while(fscanf(inFile, "%c", &data) != EOF) {
        if(data == '+' || data == '-' || data == '*' || data == '/') {
            char* dataPtr = (char*)malloc(sizeof(char));
            *dataPtr = data;
            enqueue(queue, dataPtr);
        } else if(data >= '0' && data <= '9') {
            int* dataPtr = (int*)malloc(sizeof(int));
            *dataPtr = (int)data - 48;
            enqueue(queue, dataPtr);
        }
    }

    void *item;
    char *operator;
    int *operandOne, *operandTwo;
    while(queueCount(queue) != 1) {
        dequeue(queue, &item);
        operator = (char*)item;

        queueFront(queue, &item);
        if(isNum(item)) {
            dequeue(queue, &item);
            operandOne = (int*)item;

            queueFront(queue, &item);
            if(isNum(item)) {
                dequeue(queue, &item);
                operandTwo = (int*)item;

                int *result = (int*)malloc(sizeof(int));
                switch (*operator) {
                    case '+':
                        *result = (*operandOne) + (*operandTwo);
                        break;
                    case '-':
                        *result = (*operandOne) - (*operandTwo);
                        break;
                    case '*':
                        *result = (*operandOne) * (*operandTwo);
                        break;
                    case '/':
                        *result = (*operandOne) / (*operandTwo);
                        break;
                }

                enqueue(queue, result);

                free(operator);
                free(operandOne);
                free(operandTwo);
            } else {
                enqueue(queue, operator);
                enqueue(queue, operandOne);
            }
        } else {
            enqueue(queue, operator);
        }

    }
    int* finalResult;
    dequeue(queue, &finalResult);
    printf("%d\n", *finalResult);

    free(finalResult);
    destroyQueue(queue);

    return 0;
}

bool isNum(void* data) {
    char* dataChar = (char*)data;
    return (*dataChar != '+' && *dataChar != '-' && *dataChar != '*' && *dataChar != '/');
}
