#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#define SIZE 26

typedef struct node {
    bool isLeaf;
    int value;
    char letter;
    struct node *left, *right;
} NODE;

// According to Table 6-3
int letterValue[SIZE] = {7, 2, 2, 3, 11, 2, 2, 6, 6, 1, 1, 4, 3, 7, 9, 2, 1, 6, 6, 8, 4, 1, 2, 1, 2, 1};
char huffmanCode[SIZE][10];

NODE* createHuffmanTree(void);
void makeHuffmanCode(NODE* huffmanTree, int arr[], int top);
bool checkComplete(NODE* array[], int size);
void stringToHuffman(void);
void huffmanToString(NODE* huffmanTree);

int main(int argc, char const *argv[]) {

    NODE* huffmanTree = createHuffmanTree();

    int arr[10];
    makeHuffmanCode(huffmanTree, arr, 0);

    while(1) {
        printf("\n==============================\n");
        printf("Options:\n");
        printf("(1)String to Huffman Code.\n");
        printf("(2)Huffman Code to String.\n");
        printf("(3)Show the Huffman code.\n");
        printf("(4)Quit the program.\n");
        printf("Please choose a function: ");

        int option;
        scanf("%d", &option);
        printf("==============================\n\n");

        switch (option) {
            case 1:
                stringToHuffman();
                break;
            case 2:
                huffmanToString(huffmanTree);
                break;
            case 3:
                for(int i = 0; i < 26; i++) {
                    printf("%c: %s\n", (char)i+65, huffmanCode[i]);
                }
                break;
            case 4:
                exit(0);
                break;
            default:
                printf("Please enter a valid option!\n");
                break;
        }
    }
    return(0);
}

NODE* createHuffmanTree() {
    NODE* array[SIZE];
    for(int i = 0; i < SIZE; i++) {
        array[i] = (NODE*)malloc(sizeof(NODE));
        array[i]->isLeaf = true;
        array[i]->value = letterValue[i];
        array[i]->letter = (char)(65 + i);
        array[i]->left = NULL;
        array[i]->right = NULL;
    }

    while(!checkComplete(array, SIZE)) {
        NODE initial;
        initial.value = INT_MAX;
        NODE* min1 = &initial;
        NODE* min2 = &initial;
        int min1index, min2index;
        for(int i = 0; i < SIZE; i++) {
            if(array[i]) {
                if(array[i]->value < min1->value) {
                    min2 = min1;
                    min2index = min1index;
                    min1 = array[i];
                    min1index = i;
                } else if(array[i]->value <= min2->value) {
                    min2 = array[i];
                    min2index = i;
                }
            }
        }

        NODE *newNode = (NODE*)malloc(sizeof(NODE));
        newNode->isLeaf = false;
        newNode->value = min1->value + min2->value;
        newNode->left = min1;
        newNode->right = min2;

        array[min1index] = newNode;
        array[min2index] = NULL;
    }

    for(int i = 0; i < SIZE; i++) {
        if(array[i])
            return array[i];
    }
    return NULL;
}

void makeHuffmanCode(NODE* huffmanTree, int arr[], int top) {
    if (huffmanTree->left) {
        arr[top] = 0;
        makeHuffmanCode(huffmanTree->left, arr, top + 1);
    }

    if (huffmanTree->right) {
        arr[top] = 1;
        makeHuffmanCode(huffmanTree->right, arr, top + 1);
    }

    if (huffmanTree->isLeaf) {
        for (int i = 0; i < top; i++) {
            char* buffer = (char*)malloc(sizeof(char));
            sprintf(buffer, "%d", arr[i]);
            strcat(huffmanCode[((int)(huffmanTree->letter)) - 65], buffer);
        }
    }
}

bool checkComplete(NODE* array[], int size) {
    int count = 0;
    for(int i = 0; i < size; i++) {
        if(array[i])
            count++;
        if(count > 1)
            return false;
    }

    return true;
}

void stringToHuffman(void) {
    char word[20];
    printf("Please enter a word(in upper case): ");
    scanf("%s", word);
    printf("The Huffman Code of this word is: ");
    for(int i = 0; i < strlen(word); i++) {
        printf("%s", huffmanCode[(int)word[i] - 65]);
    }
    printf("\n");
}

void huffmanToString(NODE* huffmanTree) {
    char code[50] = {0};
    printf("Please enter the Huffman Code: ");
    scanf("%s", code);

    printf("The word is: ");
    int i = 0;
    while(code[i]) {
        NODE* current = huffmanTree;
        while(!(current->isLeaf)) {
            if(code[i] == '0') {
                current = current->left;
            } else if(code[i] == '1') {
                current = current->right;
            }
            i++;
        }
        printf("%c", current->letter);
    }
    printf("\n");
}
