/*
 *  Autor: Gustavo Oliva Barnasque
 *  Matricula: 00263056
 */
#ifndef TACS_HEADER
#define TACS_HEADER

#include "ast.h"
#include "tacdefines.h"

typedef struct tac_node
{
    int type;
    HashNode* res;
    HashNode* op1;
    HashNode* op2;
    struct tac_node* prev;
    struct tac_node* next;
} TacNode;

TacNode* tacCreate(int, HashNode*, HashNode*, HashNode*);
void tacPrint(TacNode*);
void tacPrintBackwards(TacNode*);

TacNode* tacJoin(TacNode*, TacNode*);

//Code Generation
TacNode* generateCode(AstNode*);


#endif