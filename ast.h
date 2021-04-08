/*
 *  Autor: Gustavo Oliva Barnasque
 *  Matricula: 00263056
 */
#ifndef AST_HEADER
#define AST_HEADER

#include <stdio.h>
#include "hash.h"
#include "astdefines.h"

#define MAX_SONS 4 

typedef struct ast_node {
    int type;
    int dataType;
    int lineNumber;
    struct ast_node* nodes[MAX_SONS];
    HashNode* symbol;
} AstNode;

AstNode* astCreate(int, HashNode*, AstNode*, AstNode*, AstNode*, AstNode*);
void astPrint(AstNode*, int);
void printNodeType(int);
void printNodeDataType(int);

#endif