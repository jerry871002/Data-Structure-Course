#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

bool isNum(char c);

int main(int argc, char const *argv[]) {
    FILE* inFile = fopen("test.txt", "r");
    QUEUE* queue = createQueue();

    char data;
    while(fscanf(inFile, "%c", &data) != EOF) {
        printf("Data read: %c\n", data);
        if((data >= 47 && data <= 57) || data == 42 || data == 43 || data == 45) { //input only numbers and operators +, -, *, and /
            char* dataPtr = (char*)malloc(sizeof(char));
            *dataPtr = data;
            enqueue(queue, dataPtr);
            printf("Data in queue: %c\n", *dataPtr);
        }
    }

    printf("----------Calculating----------\n");
    char *item;
    char *operator, *operandOne, *operandTwo;
    int operandOneNum, operandTwoNum;
    while(queueCount(queue) != 1) {
        queueFront(queue, &item);
        if(isNum(*item)) {
            dequeue(queue, &item);
            enqueue(queue, item);
        } else {
            dequeue(queue, &item);
            operator = item;
            queueFront(queue, &item);
            if(isNum(*item)) {
                dequeue(queue, &item);
                operandOne = item;
                queueFront(queue, &item);
                if(isNum(*item)) {
                    dequeue(queue, &item);
                    operandTwo = item;
                    int* result = (int*)malloc(sizeof(int));
                    operandOneNum = (int)(*operandOne) - 48;
                    operandTwoNum = (int)(*operandTwo) - 48;
                    switch (*operator) {
                        case '+':
                            *result = operandOneNum + operandTwoNum;
                            break;
                        case '-':
                            *result = operandOneNum - operandTwoNum;
                            break;
                        case '*':
                            *result = operandOneNum * operandTwoNum;
                            break;
                        case '/':
                            *result = operandOneNum / operandTwoNum;
                            break;
                    }
                    printf("%d %c %d = %d\n", operandOneNum, *operator, operandTwoNum, *result);
                    free(operator);
                    free(operandOne);
                    free(operandTwo);
                    enqueue(queue, result);
                } else {
                    enqueue(queue, operator);
                    enqueue(queue, operandOne);
                }
            } else {
                enqueue(queue, operator);
            }
        }
    }
    int* finalResult;
    dequeue(queue, &finalResult);
    printf("The answer is %d.\n", *finalResult);

    free(finalResult);
    destroyQueue(queue);

    return 0;
}

bool isNum(char c) {
    return (c >= '0' && c <= '9');
}
