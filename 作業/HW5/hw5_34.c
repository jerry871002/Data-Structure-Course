#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

typedef struct {
    int code;
    char name[20];
    int amountInvested;
    int sharesHeld;
    float currentPrice;
} STOCK;

int compareCodeIncre(STOCK* stock1, STOCK* stock2);
int compareCodeDecre(STOCK* stock1, STOCK* stock2);
int compareGainIncre(STOCK* stock1, STOCK* stock2);
int compareGainDecre(STOCK* stock1, STOCK* stock2);
void display(LIST* list);

int main(int argc, char const *argv[]) {
    FILE* inFile = fopen("test.txt", "r");

    LIST* codeIncrease = createList(&compareCodeIncre);
    LIST* codeDecrease = createList(&compareCodeDecre);
    LIST* GainLossIncre = createList(&compareGainIncre);
    LIST* GainLossDecre = createList(&compareGainDecre);

    int code, amountInvested, sharesHeld;
    char name[20];
    float currentPrice;
    while(fscanf(inFile, "%d %s %d %d %f", &code, name, &amountInvested, &sharesHeld, &currentPrice) != EOF) {
        STOCK* stock = (STOCK*)malloc(sizeof(STOCK));
        stock->code = code;
        strcpy(stock->name, name);
        stock->amountInvested = amountInvested;
        stock->sharesHeld = sharesHeld;
        stock->currentPrice = currentPrice;

        addNode(codeIncrease, stock);
        addNode(codeDecrease, stock);
        addNode(GainLossIncre, stock);
        addNode(GainLossDecre, stock);
    }

    while(1) {
        printf("Display Options:\n");
        printf("(1)Increasing order by stock code\n");
        printf("(2)Decreasing order by stock code\n");
        printf("(3)Increasing order by stock gain or loss\n");
        printf("(4)Decreasing order by stock gain or loss\n");
        printf("(5)Quit the program\n");
        printf("Please choose the order you want to display: ");

        int option;
        scanf("%d", &option);

        switch (option) {
            case 1:
                display(codeIncrease);
                break;
            case 2:
                display(codeDecrease);
                break;
            case 3:
                display(GainLossIncre);
                break;
            case 4:
                display(GainLossDecre);
                break;
            case 5:
                exit(0);
                break;
            default:
                printf("Please enter a valid option!\n");
                break;
        }
    }
    return 0;
}

int compareCodeIncre(STOCK* stock1, STOCK* stock2) {
    return ((stock1->code) - (stock2->code));
}

int compareCodeDecre(STOCK* stock1, STOCK* stock2) {
    return ((stock2->code) - (stock1->code));
}

int compareGainIncre(STOCK* stock1, STOCK* stock2) {
    float gain1 = (stock1->sharesHeld) * (stock1->currentPrice) - (stock1->amountInvested);
    float gain2 = (stock2->sharesHeld) * (stock2->currentPrice) - (stock2->amountInvested);
    return (int)gain1 - (int)gain2;
}

int compareGainDecre(STOCK* stock1, STOCK* stock2) {
    float gain1 = (stock1->sharesHeld) * (stock1->currentPrice) - (stock1->amountInvested);
    float gain2 = (stock2->sharesHeld) * (stock2->currentPrice) - (stock2->amountInvested);
    return (int)gain2 - (int)gain1;
}

void display(LIST* list) {
    STOCK* temp;
    printf("Stock Code\t        Stock Name\tAmount Invested\t    Shares Held\t  Current Price\n");
    while(traverse(list, (int)(list->pos), &temp)) {
        printf("%10d\t%18s\t%15d\t%15d\t%15.2f\n", temp->code, temp->name, temp->amountInvested, temp->sharesHeld, temp->currentPrice);
    }
    list->pos = NULL;
}
