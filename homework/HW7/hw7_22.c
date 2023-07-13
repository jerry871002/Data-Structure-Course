// Usage: <executable> phone_numbers.txt

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "BST.h"

typedef struct {
    char name[10];
    char number[15];
} CONTACT;

int compare_contact(CONTACT* contact1, CONTACT* contact2);
void print_contact(CONTACT* contact);
void write_back(CONTACT* contact);

int main(int argc, char const *argv[]) {
    FILE* inFile = fopen(argv[1], "r");
    BST_TREE* contacts = BST_Create(&compare_contact);

    char name[10], number[15];
    while(fscanf(inFile, "%s %s", name, number) != EOF) {
        CONTACT* newContact = (CONTACT*)malloc(sizeof(CONTACT));
        strcpy(newContact->name, name);
        strcpy(newContact->number, number);
        BST_Insert(contacts, newContact);
    }

    fclose(inFile);

    while (1) {
        printf("\n==============================\n");
        printf("(1)Seach contact\n");
        printf("(2)Add contact\n");
        printf("(3)Delete contact\n");
        printf("(4)Show all contact\n");
        printf("(5)Exit the program\n");
        printf("Select a function from above: ");

        int option;
        scanf("%d", &option);
        printf("==============================\n\n");

        switch (option) {
            case 1:
                printf("Please enter a name to search: ");
                scanf("%s", name);
                CONTACT* found = BST_Retrieve(contacts, name);
                if(!found)
                    printf("Contact not found!\n");
                else
                    printf("Contact found: %s's phone number is %s\n", found->name, found->number);
                break;
            case 2:
                printf("Please enter a name and a phone number for new contact: \n");
                scanf("%s %s", name, number);

                CONTACT* newContact = (CONTACT*)malloc(sizeof(CONTACT));
                strcpy(newContact->name, name);
                strcpy(newContact->number, number);
                BST_Insert(contacts, newContact);
                break;
            case 3:
                printf("Please enter a name you want to delete: ");
                scanf("%s", name);

                CONTACT dltContact;
                bool success;
                strcpy(dltContact.name, name);
                success = BST_Delete(contacts, &dltContact);
                if(success)
                    printf("Contact deleted!\n");
                else
                    printf("Contact not found!\n");
                break;
            case 4:
                BST_Traverse(contacts, &print_contact);
                break;
            case 5:
            {
                // Make the file empty
                FILE* outFile = fopen("input_7_22.txt", "w");
                fclose(outFile);
                BST_Traverse(contacts, &write_back);
                exit(0);
            }
            default:
                printf("Please enter a valid option!\n");
                break;
        }
    }

    return 0;
}

int compare_contact(CONTACT* contact1, CONTACT* contact2) {
    return strcmp(contact1->name, contact2->name);
}

void print_contact(CONTACT* contact) {
    printf("%10s %15s\n", contact->name, contact->number);
}

void write_back(CONTACT* contact) {
    FILE* outFile = fopen("input_7_22.txt", "a");
    fprintf(outFile, "%s %s\n", contact->name, contact->number);
    fclose(outFile);
}
