// Usage: <executable> students.txt

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    void* dataPtr;
    struct node* next;
} NODE;

typedef struct {
    int id;
    float average;
} student;

NODE* createNode(void* itemPtr);
NODE* addNode(NODE* head, NODE* newNode);
void printNodes(NODE* nodes);

int main(int argc, char* argv[]) {
    FILE* inFilePtr;
    inFilePtr = fopen(argv[1], "r");

    int id;
    float average;
    NODE* students = NULL;

    while(fscanf(inFilePtr, "%d %f", &id, &average) != EOF) {
        student* newStudent;
        newStudent = (student*)malloc(sizeof(student));
        newStudent->id = id;
        newStudent->average = average;

        NODE* newNode;
        newNode = createNode(newStudent);
        students = addNode(students, newNode);
    }

    printNodes(students);
    fclose(inFilePtr);
    return 0;
}

NODE* createNode(void* itemPtr) {
    NODE* nodePtr;
    nodePtr = (NODE*)malloc(sizeof(NODE));
    nodePtr->dataPtr = itemPtr;
    nodePtr->next = NULL;
    return nodePtr;
}

NODE* addNode(NODE* head, NODE* newNode) {
    if(head == NULL){
        head = newNode;
        return head;
    }

    NODE* last = head;
    while(last->next != NULL)
        last = last->next;

    last->next = newNode;
    return head;
}

void printNodes(NODE* nodes) {
    while(nodes) {
        printf("ID: %d, Average: %f\n", ((student*)nodes->dataPtr)->id, ((student*)nodes->dataPtr)->average);
        nodes = nodes->next;
    }
}
