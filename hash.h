/*
    Autor: Gustavo Oliva Barnasque
    Matricula: 00263056
*/

#define HASH_SIZE 997

typedef struct hash_node {
    int type;
    char* text;
    struct hash_node* next;
} HashNode;

void hashInit();
int hashCalculateAddress(char*);
HashNode* hashFind(char*);
HashNode* hashInsert(int, char*);
void printHashTable();
