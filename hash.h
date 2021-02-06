#include <stdlib.h>

#define HASH_SIZE 997

typedef struct hash_node {
    int type;
    char* text;
    struct hash_node* next;
} HashNode;

void init();
int calculateAddress(char*);
HashNode* find(char*);
HashNode* insert(int, char*);
void printHashTable();
