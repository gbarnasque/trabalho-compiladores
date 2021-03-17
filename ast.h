/*
 *  Autor: Gustavo Oliva Barnasque
 *  Matricula: 00263056
 */
#ifndef AST_HEADER
#define AST_HEADER

#include <stdio.h>
#include "hash.h"

#define MAX_SONS 4 

#define AST_SYMBOL 1
#define AST_ADD 2
#define AST_SUB 2
#define AST_MULT 4
#define AST_DIV 5


typedef struct ast_node {
    int type;
    struct ast_node* nodes[MAX_SONS];
    HashNode* symbol;
} AstNode;

AstNode* astCreate(int, HashNode*, AstNode*, AstNode*, AstNode*, AstNode*);
void astPrint(AstNode*, int);

#endif