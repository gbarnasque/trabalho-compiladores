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
TacNode* tripleTacJoinLast(TacNode*, TacNode*, TacNode*);
TacNode* quadTacJoinLast(TacNode*, TacNode*, TacNode*, TacNode*);
TacNode* tripleTacJoinFirst(TacNode*, TacNode*, TacNode*);
TacNode* quadTacJoinFirst(TacNode*, TacNode*, TacNode*, TacNode*); 

HashNode* getRes(TacNode*);

// Makes to make life easier
TacNode* makeUnaryOperation(int, TacNode*);
TacNode* makeBinaryOperation(int, TacNode*, TacNode*);
TacNode* makeIfThen(TacNode*, TacNode*);

//Code Generation
TacNode* generateCode(AstNode*);


#endif