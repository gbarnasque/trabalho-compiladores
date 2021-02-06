//#include "hash.h"

HashNode* hashTable[HASH_SIZE];

void hashInit() {
    int i;
    for(i=0; i<HASH_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

int hashCalculateAddress(char* text) {
    int address = 1;
    int i;
    for(i=0; i<strlen(text); i++) {
        address = (address * text[i]) % HASH_SIZE + 1;
    }
    return address-1;
}

HashNode* hashFind(char* text) {
    HashNode* ret = NULL;
    int address = hashCalculateAddress(text);
    
    //if(hashTable[address] == NULL)
        //return NULL;

    ret = hashTable[address];
    while(ret != NULL && (strcmp(ret->text, text) != 0)) {
        ret = ret->next;
    }

    return ret;
}

HashNode* hashInsert(int type, char* text) {
    HashNode* ret;
    int address;

    if((ret = hashFind(text)) != NULL)
        return ret;
    
    address = hashCalculateAddress(text);

    ret = (HashNode*) malloc(sizeof(HashNode));
    ret->type = type;
    ret->text = (char*) malloc((strlen(text)+1) * sizeof(char));
    strcpy(ret->text, text);
    ret->next = hashTable[address];
    hashTable[address] = ret;
    return ret;
}

void printHashTable() {
    int i;
    HashNode* node;
    for(i=0; i<HASH_SIZE; i++) {
        node = hashTable[i];
        while(node != NULL) {
            printf("Tabela[%d] contem token %d - %s\n", i, node->type, node->text);
            node = node->next;
        }
    }
}
