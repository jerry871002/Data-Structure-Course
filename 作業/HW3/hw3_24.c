#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stack.h"

typedef struct {
    int row;
    int col;
} SPOT;

int main(int argc, char const *argv[]) {
    int maze[10][12] = {{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
                        {1, 0, 0, 0, 1, 1, 0, 1, 0, 1, 0, 1},
                        {1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 1},
                        {1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 1},
                        {1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
                        {1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1},
                        {1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
                        {1, 1, 1, 1, 0, 1, 1, 1, 0, 1, 0, 1},
                        {1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
                        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    for(int i = 0; i < 10; i++) {
        for(int j = 0;j < 12; j++) {
            printf("%d ", maze[i][j]);
        }
        printf("\n");
    }

    int start_row, start_col;
    printf("Please enter a spot to start: ");
    while(1) {
        scanf("%d %d", &start_row, &start_col);
        if((start_row <= 10) && (start_col <= 12) && (maze[start_row][start_col] == 0))
            break;
        printf("Please enter a valid spot: ");
    }
    SPOT* currentSpot = (SPOT*)malloc(sizeof(SPOT));
    currentSpot->row = start_row;
    currentSpot->col = start_col;

    STACK* visitedSpots = createStack();
    STACK* alternativeSpots = createStack();

    while(1) {
        if((currentSpot->row == 0) || (currentSpot->row == 9) || (currentSpot->col) == 0 || (currentSpot->col) == 11) {
            printf("(%d, %d) -> Exit\n", currentSpot->row, currentSpot->col);
            break;
        }

        printf("(%d, %d) -> ", currentSpot->row, currentSpot->col);

        int count = 0;
        bool check;

        //up
        check = true;
        if(maze[(currentSpot->row)-1][currentSpot->col] == 1)
            check = false;
        if(!emptyStack(visitedSpots)) {
            if((((SPOT*)stackTop(visitedSpots))->row == ((currentSpot->row)-1)) &&
            (((SPOT*)stackTop(visitedSpots))->col == (currentSpot->col)))
                check = false;
        }
        if(check) {
            SPOT* upSpot = (SPOT*)malloc(sizeof(SPOT));
            upSpot->row = (currentSpot->row)-1;
            upSpot->col = currentSpot->col;
            pushStack(alternativeSpots, upSpot);
            count++;
            //printf("**Push up**");
        }

        //right
        check = true;
        if(maze[currentSpot->row][(currentSpot->col)+1] == 1)
            check = false;
        if(!emptyStack(visitedSpots)) {
            if((((SPOT*)stackTop(visitedSpots))->row == ((currentSpot->row))) &&
            (((SPOT*)stackTop(visitedSpots))->col == ((currentSpot->col)+1)))
                check = false;
        }
        if(check) {
            SPOT* rightSpot = (SPOT*)malloc(sizeof(SPOT));
            rightSpot->row = currentSpot->row;
            rightSpot->col = (currentSpot->col)+1;
            pushStack(alternativeSpots, rightSpot);
            count++;
            //printf("**Push right**");
        }

        //down
        check = true;
        if(maze[(currentSpot->row)+1][currentSpot->col] == 1)
            check = false;
        if(!emptyStack(visitedSpots)) {
            if((((SPOT*)stackTop(visitedSpots))->row == ((currentSpot->row)+1)) &&
            (((SPOT*)stackTop(visitedSpots))->col == ((currentSpot->col))))
                check = false;
        }
        if(check) {
            SPOT* downSpot = (SPOT*)malloc(sizeof(SPOT));
            downSpot->row = (currentSpot->row)+1;
            downSpot->col = currentSpot->col;
            pushStack(alternativeSpots, downSpot);
            count++;
            //printf("**Push down**");
        }

        //left
        check = true;
        if(maze[currentSpot->row][(currentSpot->col)-1] == 1)
            check = false;
        if(!emptyStack(visitedSpots)) {
            if((((SPOT*)stackTop(visitedSpots))->row == (currentSpot->row)) &&
            (((SPOT*)stackTop(visitedSpots))->col == ((currentSpot->col)-1)))
                check = false;
        }
        if(check) {
            SPOT* leftSpot = (SPOT*)malloc(sizeof(SPOT));
            leftSpot->row = currentSpot->row;
            leftSpot->col = (currentSpot->col)-1;
            pushStack(alternativeSpots, leftSpot);
            count++;
            //printf("**Push left**");
        }

        //printf("**count is %d**", count);
        if(count > 1) {
            SPOT* decisionSpot = (SPOT*)malloc(sizeof(SPOT));
            decisionSpot->row = -1;
            decisionSpot->col = -1;
            pushStack(visitedSpots, decisionSpot);
        }

        if(count == 0) {
            printf("Dead End -> ");
            while(((SPOT*)stackTop(visitedSpots))->row > 0) {
                printf("(%d, %d) -> ", currentSpot->row, currentSpot->col);
                currentSpot = (SPOT*)popStack(visitedSpots);
                if(emptyStack(visitedSpots)) {
                    printf("This maze has no exit!!\n");
                    return 0;
                }
            }
            printf("*(%d, %d)* -> ", currentSpot->row, currentSpot->col);
            popStack(visitedSpots);
        }

        pushStack(visitedSpots, currentSpot);
        currentSpot = (SPOT*)popStack(alternativeSpots);
    }

    return 0;
}
