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
    int idleTime;
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
    stats->numCust = stats-> totSvcTime = stats->totWaitTime = stats->maxQueueSize = stats->idleTime = 0;

    int clock, serviceProvided, maxServiceTime;
    printf("Please enter the length of time (in hour) that the service is provided: ");
    scanf("%d", &serviceProvided);
    printf("Please enter the maximum service time (in minute): ");
    scanf("%d", &maxServiceTime);

    int* custNum = (int*)malloc(sizeof(int));
    *custNum = 0;

    printf("\nClock Time\tCall Num\tArrive Time\tWait time\tStart Time\tSvc Time\tQueue Size\n");

    for(clock = 1; clock <= serviceProvided * 60 || *moreCusts; clock++) {
        newCustomer(queue, clock, custNum, serviceProvided);
        severFree(queue, clock, status, moreCusts, maxServiceTime);
        svcComplete(queue, clock, status, stats, moreCusts);

        if(!emptyQueue(queue))
            *moreCusts = true;
        else if(clock > status->startTime + status->svcTime - 1) {
            printf("Idle at clock = %d\n", clock);
            (stats->idleTime)++;
        }
    }

    printStats(stats);

    destroyQueue(queue);
    free(moreCusts);
    free(status);
    free(stats);
    free(custNum);

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

        printf("%10d\t%8d\t%11d\t%9d\t%10d\t%8d\t%10d\n", clock, status->custNum, status->arriveTime, waitTime, status->startTime, status->svcTime, queueCount(queue));

        *moreCusts = false;
    }
}

void printStats(simStats* stats) {
    printf("\nSimulation Statistics:\n");
    printf("Total calls: %d calls\n", stats->numCust);
    printf("Total idle time: %d minutes\n", stats->idleTime);
    printf("Total wait time: %d minutes\n", stats->totWaitTime);
    printf("Total service time: %d minutes\n", stats->totSvcTime);
    printf("Maximun queue size: %d\n", stats->maxQueueSize);
    float avgWaitTime = (float)stats->totWaitTime / stats->numCust;
    printf("Average wait time: %.2f minutes\n", avgWaitTime);
    float avgSvcTime = (float)stats->totSvcTime / stats->numCust;
    printf("Average service time: %.2f minutes\n\n", avgSvcTime);
}
