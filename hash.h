/*
 *  Autor: Gustavo Oliva Barnasque
 *  Matricula: 00263056
 */

#ifndef HASH_HEADER
#define HASH_HEADER

#define SYMBOL_LIT_INT    1
#define SYMBOL_LIT_CHAR   2
#define SYMBOL_LIT_STRING 3
#define SYMBOL_LIT_TRUE   4
#define SYMBOL_LIT_FALSE  5
#define SYMBOL_IDENTIFIER 6
#define SYMBOL_VARIABLE   7
#define SYMBOL_FUNCTION   8
#define SYMBOL_VECTOR     9

#define DATATYPE_INT     1
#define DATATYPE_CHAR    2
#define DATATYPE_BOOL    3
#define DATATYPE_POINTER 4


#define HASH_SIZE 997

typedef struct hash_node {
    int type;
    int dataType;
    char* text;
    struct hash_node* next;
    int numParameters;
    int* dataTypesParameters;
} HashNode;

void hashInit();
int hashCalculateAddress(char*);
HashNode* hashFind(char*);
HashNode* hashInsert(int, char*);
void printHashTable();
int hashCheckUndeclared();
char* getSymbolText(int);
char* getDatatypeText(int);

#endif