// Usage: <executable> < polynomial.txt

#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct {
    int coeff;
    int power;
} TERM;

int comparePower(TERM* term1, TERM* term2);
void readPolynomial(LIST* polynomial);
void addPolynomial(LIST* summand, LIST* addend);
void printPolynomial(LIST* polynomial);

int main(int argc, char const *argv[]) {
    LIST* polynomial1 = createList(&comparePower);
    LIST* polynomial2 = createList(&comparePower);
    LIST* result = createList(&comparePower);

    readPolynomial(polynomial1);
    readPolynomial(polynomial2);

    addPolynomial(result, polynomial1);
    addPolynomial(result, polynomial2);

    printf("Polynomial 1:\n");
    printPolynomial(polynomial1);
    printf("Polynomial 2:\n");
    printPolynomial(polynomial2);
    printf("Result Polynomial:\n");
    printPolynomial(result);

    return 0;
}

int comparePower(TERM* term1, TERM* term2) {
    return (term2->power) - (term1->power);
}

void readPolynomial(LIST* polynomial) {
    while(1) {
        int coeff, power;
        scanf("%d %d", &coeff, &power);
        if(coeff == 0 && power == 0)
            break;

        TERM* term = (TERM*)malloc(sizeof(TERM));
        term->coeff = coeff;
        term->power = power;

        addNode(polynomial, term);
    }
    //printf("Finish reading\n");
}

void addPolynomial(LIST* summand, LIST* addend) {
    TERM *termAddend, *termSummand;
    while(traverse(addend, (int)(addend->pos), &termAddend)) {
        if(searchList(summand, termAddend, &termSummand))
            termSummand->coeff += termAddend->coeff;
        else {
            TERM* newTerm = (TERM*)malloc(sizeof(TERM));
            newTerm->coeff = termAddend->coeff;
            newTerm->power = termAddend->power;
            addNode(summand, newTerm);
        }
    }
    addend->pos = NULL;
}

void printPolynomial(LIST* polynomial) {
    TERM* term;
    while(traverse(polynomial, (int)(polynomial->pos), &term)) {
        if(term->coeff == 0)
            continue;
        if((polynomial->pos != polynomial->head) && term->coeff > 0)
            printf("+");
        printf("%d*x%d", term->coeff, term->power);
    }

    polynomial->pos = NULL;
    printf("\n");
    //printf("\nFinish printing\n");
}
