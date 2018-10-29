#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

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

void newCustomer(QUEUE* queue, int clock, int* custNum, int serviceProvided);
void severFree(QUEUE* queue, int clock, custStatus* status, bool* moreCusts, int maxServiceTime);
void svcComplete(QUEUE* queue, int clock, custStatus* status, simStats* stats, bool* moreCusts);
void printStats(simStats* stats);

int main(int argc, char const *argv[]) {
    srand(time(NULL));
    QUEUE *queue = createQueue();

    bool* moreCusts = (bool*)malloc(sizeof(bool));
    *moreCusts = false;

    custStatus* status = (custStatus*)malloc(sizeof(custStatus));
    status->custNum = status->arriveTime = status->startTime = status->svcTime = 0;

    simStats* stats = (simStats*)malloc(sizeof(simStats));
    stats->numCust = stats-> totSvcTime = stats->totWaitTime = stats->maxQueueSize = 0;

    int clock, serviceProvided, maxServiceTime;
    printf("Please enter the length of time (in hour) that the service is provided: ");
    scanf("%d", &serviceProvided);
    printf("Please enter the maximum service time (in minute): ");
    scanf("%d", &maxServiceTime);

    int* custNum = (int*)malloc(sizeof(int));
    *custNum = 0;

    printf("\nCust Num\tArrive Time\tStart Time\tSvc Time\tWait time\tQueue Size\n");

    for(clock = 1; clock <= serviceProvided * 60 || *moreCusts; clock++) {
        newCustomer(queue, clock, custNum, serviceProvided);
        severFree(queue, clock, status, moreCusts, maxServiceTime);
        svcComplete(queue, clock, status, stats, moreCusts);

        if(!emptyQueue(queue))
            *moreCusts = true;
    }

    printStats(stats);

    return 0;
}

void newCustomer(QUEUE* queue, int clock, int* custNum, int serviceProvided) {
    int randomNum = rand() % 9;
    if(randomNum > 4 && clock < serviceProvided * 60) {
        (*custNum)++;
        custData* cust = (custData*)malloc(sizeof(custData));
        cust->custNum = *custNum;
        cust->arriveTime = clock;
        enqueue(queue, cust);
    }
}

void severFree(QUEUE* queue, int clock, custStatus* status, bool* moreCusts, int maxServiceTime) {
    if(clock > status->startTime + status->svcTime - 1) {
        if(!emptyQueue(queue)) {
            custData* cust;
            dequeue(queue, &cust);
            status->custNum = cust->custNum;
            status->arriveTime = cust->arriveTime;
            status->startTime = clock;
            status->svcTime = rand() % maxServiceTime + 1;
            *moreCusts = true;
        }
    }
}

void svcComplete(QUEUE* queue, int clock, custStatus* status, simStats* stats, bool* moreCusts) {
    if(clock == status->startTime + status->svcTime - 1) {
        int waitTime = status->startTime - status->arriveTime;
        stats->numCust++;
        stats->totSvcTime += status->svcTime;
        stats->totWaitTime += waitTime;

        if(stats->maxQueueSize < queueCount(queue))
            stats->maxQueueSize = queueCount(queue);

        printf("%8d\t%11d\t%10d\t%8d\t%9d\t%10d\n", status->custNum, status->arriveTime, status->startTime, status->svcTime, waitTime, queueCount(queue));

        *moreCusts = false;
    }
}

void printStats(simStats* stats) {
    printf("\nSimulation Statistics:\n");
    printf("Total Customer: %d\n", stats->numCust);
    printf("Total Service Time: %d minutes\n", stats->totSvcTime);
    float avgSvcTime = (float)stats->totSvcTime / stats->numCust;
    printf("Average service time: %.2f minutes\n", avgSvcTime);
    float avgWaitTime = (float)stats->totWaitTime / stats->numCust;
    printf("Average wait time: %.2f minutes\n", avgWaitTime);
    printf("Maximun queue size: %d\n\n", stats->maxQueueSize);
}
