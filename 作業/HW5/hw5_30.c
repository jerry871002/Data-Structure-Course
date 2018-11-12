#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"

int compare(void* argu1, void* argu2);
void polynomial(LIST* polynomial, int num);

int main(int argc, char const *argv[]) {
    int num1, num2;
    printf("Please enter the first number: ");
    scanf("%d", &num1);
    printf("Please enter the second number: ");
    scanf("%d", &num2);

    LIST* numList1 = createList(&compare);
    LIST* numList2 = createList(&compare);
    LIST* result = createList(&compare);

    polynomial(numList1, num1);
    polynomial(numList2, num2);

    int carry = 0;
    bool firstNum, secondNum;
    int *currentDigit1, *currentDigit2;

    while(1) {
        firstNum = traverse(numList1, (int)(numList1->pos), &currentDigit1);
        secondNum = traverse(numList2, (int)(numList2->pos), &currentDigit2);
        if(firstNum == false && secondNum == false && carry == 0)
            break;

        int digit1, digit2;
        if(firstNum)
            digit1 = (*currentDigit1);
        else
            digit1 = 0;
        if(secondNum)
            digit2 = (*currentDigit2);
        else
            digit2 = 0;

        int* singleDigit = (int*)malloc(sizeof(int));
        *singleDigit = digit1 + digit2 + carry;
        if(*singleDigit > 9) {
            *singleDigit -= 10;
            carry = 1;
        } else
            carry = 0;

        addNode(result, singleDigit);
    }

    int* digit;
    int multiplier = 1;
    int resultNum = 0;
    while(traverse(result, (int)(result->pos), &digit)) {
        resultNum += ((*digit) * multiplier);
        multiplier *= 10;
    }
    printf("%d\n", resultNum);

    return 0;
}

int compare(void* argu1, void* argu2) {
    return 1;
}

void polynomial(LIST* polynomial, int num) {
    while(num) {
        int* singleDigit = (int*)malloc(sizeof(int));
        *singleDigit = num % 10;
        addNode(polynomial, singleDigit);
        num /= 10;
    }
}
