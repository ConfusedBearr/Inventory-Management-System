//Coded By Rodrigo Peixoto
//Coded On 12/03/2023
//inventory.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLEN 19
#define TABLESIZE 300007
#define totalMoney 100000

typedef struct item {
    char name[MAXLEN + 1];
    int quantity;
    int saleprice;
} item;

typedef struct node {
    item* iPtr;
    struct node* next;
} node;

typedef struct hashtable {
    node** lists;
    int size;
} hashtable;

int hashfunc(char* word, int size);
hashtable* initiHashTable(int size);
void initializeItem(item* ptr, char* name, int quantity, int saleprice);
node* initializeNode(item* iPtr);
void buyItem(hashtable* table, char* itemName, int quantity, int totalPrice, int* totalCash, int *totalComplexity);
void sellItem(hashtable* table, char* itemName, int quantity, int* totalCash, int *totalComplexity);
void changePrice(hashtable* table, char* itemName, int newPrice, int *totalComplexity);

int main() {
    int n;
    scanf("%d",&n);

    hashtable* inventory = initiHashTable(TABLESIZE);

    int totalCash = totalMoney;
    int totalComplexity;

    while(n > 0){
        char action[12];
        char item[19];
        int numofItem;
        int priceofItem;
        int newPrice;
        scanf("%s",action);

        if(strcmp(action,"buy") == 0){
            scanf("%s %d %d", item, &numofItem,&priceofItem);
            buyItem(inventory, item, numofItem, priceofItem, &totalCash,&totalComplexity);
        } else if(strcmp(action, "sell") == 0){
            scanf("%s %d", item,&numofItem);
            sellItem(inventory, item, numofItem, &totalCash, &totalComplexity);
        } else if(strcmp(action,"change_price") == 0 ){
            scanf("%s %d", item, &newPrice);
            changePrice(inventory, item, newPrice, &totalComplexity);
        }

        n--;
    }

    // Print total cash on hand and total complexity
    printf("%d\n", totalCash);
    printf("%d\n", totalComplexity);

    // Free memory allocated for the hashtable and its nodes
    for (int i = 0; i < inventory->size; ++i) {
        node* current = inventory->lists[i];
        while (current != NULL) {
            node* temp = current;
            current = current->next;
            free(temp->iPtr);
            free(temp);
        }
    }
    free(inventory->lists);
    free(inventory);

    return 0;
}

int hashfunc(char* word, int size) {
    int len = strlen(word);
    int res = 0;
    for (int i=0; i<len; i++)
        res = (1151*res + (word[i]-'a'))%size;
    return res;
}

hashtable* initiHashTable(int size) {
    hashtable* table = (hashtable*)malloc(sizeof(hashtable));
    if (table != NULL) {
        table->size = size;
        table->lists = (node**)calloc(size, sizeof(node*));
    }
    return table;
}

void initializeItem(item* ptr, char* name, int quantity, int saleprice){
    strncpy(ptr->name, name, MAXLEN);
    ptr->name[MAXLEN] = '\0';
    ptr->quantity = quantity;
    ptr->saleprice = saleprice;
}

node* initializeNode(item* iPtr){
    node* newNode = (node*)malloc(sizeof(node));
    if (newNode != NULL) {
        newNode->iPtr = iPtr;
        newNode->next = NULL;
    }
    return newNode;
}

void buyItem(hashtable* table, char* itemName, int quantity, int totalPrice, int *totalCash, int *totalComplexity){
    int index = hashfunc(itemName, table->size);

    // Check if the item is already in the inventory
    node* current = table->lists[index];
    (*totalComplexity)++;
    // Traverse the linked list to find the item
    while (current != NULL) {
        (*totalComplexity)++;
        if (strcmp(current->iPtr->name, itemName) == 0) {
            current->iPtr->quantity += quantity;
            *totalCash -= totalPrice;
            printf("%s %d %d\n", current->iPtr->name, current->iPtr->quantity, *totalCash);
            return;
        }
        current = current->next;
        (*totalComplexity)++;
    }

    (*totalComplexity)++;
    item* newItem = (item*)malloc(sizeof(item));
    if (newItem != NULL) {
        initializeItem(newItem, itemName, quantity, totalPrice / quantity);

        node* newNode = initializeNode(newItem);
        if (newNode != NULL) {
            newNode->next = table->lists[index];
            table->lists[index] = newNode;

            *totalCash -= totalPrice;
            printf("%s %d %d\n", newItem->name, newItem->quantity, *totalCash);
        }
    } else {
        printf("Memory allocation failed.\n");
    }
}

void sellItem(hashtable* table, char* itemName, int quantity, int* totalCash, int *totalComplexity) {
    int index = hashfunc(itemName, table->size);
    node* current = table->lists[index];
    (*totalComplexity)++;

    while (current != NULL) {
        (*totalComplexity)++;
        if (strcmp(current->iPtr->name, itemName) == 0) {
            // Calculate total price based on the current sale price
            int totalPrice = current->iPtr->saleprice * quantity;

            if (current->iPtr->quantity >= quantity) {
                (*totalComplexity)++;
                current->iPtr->quantity -= quantity;
                *totalCash += totalPrice;
                printf("%s %d %d\n", current->iPtr->name, current->iPtr->quantity, *totalCash);
            } else {
                (*totalComplexity)++;
                // Sell available quantity if requested quantity exceeds stock
                int soldQuantity = current->iPtr->quantity;
                current->iPtr->quantity = 0;
                *totalCash += current->iPtr->saleprice * soldQuantity;
                printf("%s %d %d\n", current->iPtr->name, current->iPtr->quantity, *totalCash);
            }
            return;
        }
        (*totalComplexity)++;
        current = current->next;

    }

    printf("Item not found in inventory.\n");
}

void changePrice(hashtable* table, char* itemName, int newPrice, int *totalComplexity){
    int index = hashfunc(itemName, table->size);

    // Search for the item in the inventory
    node* current = table->lists[index];
    (*totalComplexity)++;

    while (current != NULL) {
        (*totalComplexity)++;
        if (strcmp(current->iPtr->name, itemName) == 0) {
            // Item found in the inventory, update its sale price
            current->iPtr->saleprice = newPrice;
            return;
        }
        (*totalComplexity)++;
        current = current->next;

    }
    // Item not found
    printf("Item not found in inventory.\n");
}