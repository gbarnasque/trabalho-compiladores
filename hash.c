/*
 *  Autor: Gustavo Oliva Barnasque
 *  Matricula: 00263056
 */

#include "hash.h"

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
    ret->dataType = 0;
    ret->numParameters = 0;
    ret->dataTypesParameters = NULL;
    hashTable[address] = ret;
    return ret;
}

void printHashTable() {
    int i;
    HashNode* node;
    for(i=0; i<HASH_SIZE; i++) {
        node = hashTable[i];
        while(node != NULL) {
            fprintf(stderr, "Tabela[%d] has %s, type: %s, datatype: %s \n", i, node->text, getSymbolText(node->type), getDatatypeText(node->dataType));
            node = node->next;
        }
    }
}

int hashCheckUndeclared() {
    int undeclared = 0;
    int i;
    HashNode* node;
    for(i=0; i<HASH_SIZE; i++) {
        node = hashTable[i];
        while(node != NULL) {
            if(node->type == SYMBOL_IDENTIFIER) {
                fprintf(stderr, "[S02] Semantic ERROR: identifier %s not declared\n", node->text);
                ++undeclared;
            }
            node = node->next;
        }
    }
    return undeclared;
}

char* getSymbolText(int s) {
    switch (s)
    {
        case SYMBOL_LIT_INT:
            return "SYMBOL_LIT_INT";
        case SYMBOL_LIT_CHAR:
            return "SYMBOL_LIT_CHAR";
        case SYMBOL_LIT_STRING:
            return "SYMBOL_LIT_STRING";
        case SYMBOL_LIT_TRUE:
            return "SYMBOL_LIT_TRUE";
        case SYMBOL_LIT_FALSE:
            return "SYMBOL_LIT_FALSE";
        case SYMBOL_IDENTIFIER:
            return "SYMBOL_IDENTIFIER";
        case SYMBOL_VARIABLE:
            return "SYMBOL_VARIABLE";
        case SYMBOL_FUNCTION:
            return "SYMBOL_FUNCTION";
        case SYMBOL_VECTOR:
            return "SYMBOL_VECTOR";
        default:
            break;
    }
    return "";
}
char* getDatatypeText(int dt) {
    switch (dt)
    {
        case DATATYPE_INT:
            return "DATATYPE_INT";
        case DATATYPE_CHAR:
            return "DATATYPE_CHAR";
        case DATATYPE_BOOL:
            return "DATATYPE_BOOL";
        case DATATYPE_POINTER:
            return "DATATYPE_POINTER";
        default:
            break;
    }
    return "";
}

HashNode* makeTemp() {
    static int serial = 0;
    char buffer[256] = "";
    sprintf(buffer, "MyW31rd_T3mP_%d", serial++);
    return hashInsert(SYMBOL_VARIABLE, buffer);
}

HashNode* makeLabel() {
    static int serial = 0;
    char buffer[256] = "";
    sprintf(buffer, "MyL4b3l_T3mP_%d", serial++);
    return hashInsert(SYMBOL_LABEL, buffer);
}