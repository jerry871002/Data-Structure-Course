#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "0610780_5_26.h"

typedef struct {
    char name[20];
    LIST* scores;
} STUDENT;

int scoreCompare(int* score1, int* score2);

int main(int argc, char const *argv[]) {
    if(argc != 2) {
        printf("Usage: [program_name] [input_file_name], e.g. ./a.out StudentName.txt\n");
        exit(1);
    }

    FILE* inFile = fopen(argv[1], "r");

    LIST* stdList = createList(&strcmp);

    char name[20];
    while(fscanf(inFile, "%[a-zA-Z ]\n", name) != EOF) {
        STUDENT* student = (STUDENT*)malloc(sizeof(STUDENT));
        strcpy(student->name, name);
        student->scores = createList(&scoreCompare);

        printf("Please enter scores of %s\n", student->name);
        for(int i = 0; i < 4; i++) {
            int score;
            scanf("%d", &score);
            if(score >= 0) {
                int* scoreIn = (int*)malloc(sizeof(int));
                *scoreIn = score;
                addNode(student->scores, scoreIn);
            } else
                break;
        }
        addNode(stdList, student);
    }

    STUDENT* currentStudent;
    int* currentScore;
    printf("\n==========Average Score==========\n");
    while(traverse(stdList, (int)(stdList->pos), &currentStudent)) {
        printf("%s: ", currentStudent->name);

        int sum = 0;
        while(traverse(currentStudent->scores, (int)(currentStudent->scores->pos), &currentScore))
            sum += (*currentScore);

        if((currentStudent->scores->count) != 0) {
            float average = (float)sum / (currentStudent->scores->count);
            printf("%.2f\n", average);
        } else
            printf("No score\n");
    }
    return 0;
}

int scoreCompare(int* score1, int* score2) {
    return *score1 - *score2;
}
