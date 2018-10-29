#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
    int custNum;
    int arriveTime;
} custData;

typedef struct {
    int custNum;
    int arriveTime;
    int startTime;
    int svcTime;
} custStatus;

typedef struct {
    int numCust;
    int totSvcTime;
    int totWaitTime;
    int maxQueueSize;
} simStats;

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    QUEUE *queue = createQueue();
    bool moreCusts;

    custStatus* status = (custStatus*)malloc(sizeof(custStatus));
    simStats* stats = (simStats*)malloc(sizeof(simStats));
    stats->numCust = stats-> totSvcTime = stats->totWaitTime = stats->maxQueueSize = 0;

    int clock, serviceProvided, maxServiceTime;
    printf("Please enter the length of time (in hour) that the service is provided: ");
    scanf("%d\n", &serviceProvided);
    printf("Please enter the maximum service time (in minute): ");
    scanf("%d\n", &maxServiceTime);

    int* custNum = (int*)malloc(sizeof(int));
    *custNum = 0
    for(clock = 1; clock <= serviceProvided * 60 || moreCusts; currentClock++) {
        newCustomer(queue, clock, custNum);
    }

    return 0;
}

newCustomer(QUEUE* queue, int clock, int* custNum) {
    int randomNum = rand() % 9;
    if(randomNum > 4) {
        custNum++;
        custData* cust = (custData*)malloc(sizeof(custData));
        cust->custNum = *custNum;
        cust->arriveTime = clock;
        enqueue(queue, cust);
    }
}
