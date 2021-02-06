//#include "hash.h"

HashNode* hashTable[HASH_SIZE];

void init() {
    int i;
    for(i=0; i<HASH_SIZE; i++) {
        hashTable[i] = NULL;
    }
}

int calculateAddress(char* text) {
    int address = 1;
    int i;
    for(i=0; i<strlen(text); i++) {
        address = (address * text[i]) % HASH_SIZE + 1;
    }
    return address-1;
}

HashNode* find(char* text) {
    HashNode* ret = NULL;
    int address = calculateAddress(text);
    

    //if(hashTable[address] == NULL)
        //return NULL;

    ret = hashTable[address];
    while(ret != NULL && (strcmp(ret->text, text) != 0)) {
        ret = ret->next;
    }

    return ret;
}

HashNode* insert(int type, char* text) {
    HashNode* ret;
    int address;

    if((ret = find(text)) != NULL)
        return ret;
    
    address = calculateAddress(text);

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
            printf("Tabela[%d] contem %s\n", i, node->text);
            node = node->next;
        }
    }
}
